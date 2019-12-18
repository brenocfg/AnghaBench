#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct adb_request {int* reply; int sent; int complete; int* data; int reply_len; int /*<<< orphan*/  (* done ) (struct adb_request*) ;struct adb_request* next; int /*<<< orphan*/  reply_expected; int /*<<< orphan*/  nbytes; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t ACR ; 
 size_t B ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CTLR_IRQ ; 
 size_t IFR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 size_t SR ; 
 int SR_INT ; 
 int SR_OUT ; 
 int ST_CMD ; 
 int ST_EVEN ; 
 int ST_IDLE ; 
 int ST_MASK ; 
 int /*<<< orphan*/  adb_input (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  autopoll_devs ; 
 struct adb_request* current_req ; 
 int /*<<< orphan*/  data_index ; 
#define  idle 131 
 int last_status ; 
 int /*<<< orphan*/  macii_autopoll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macii_queue_poll () ; 
 int /*<<< orphan*/  macii_start () ; 
 int macii_state ; 
 int /*<<< orphan*/  need_autopoll () ; 
#define  read_done 130 
#define  reading 129 
 int reading_reply ; 
 int* reply_buf ; 
 int reply_len ; 
 int* reply_ptr ; 
#define  sending 128 
 int srq_asserted ; 
 int status ; 
 int /*<<< orphan*/  stub1 (struct adb_request*) ; 
 int /*<<< orphan*/  stub2 (struct adb_request*) ; 
 int* via ; 

__attribute__((used)) static irqreturn_t macii_interrupt(int irq, void *arg)
{
	int x;
	static int entered;
	struct adb_request *req;

	if (!arg) {
		/* Clear the SR IRQ flag when polling. */
		if (via[IFR] & SR_INT)
			via[IFR] = SR_INT;
		else
			return IRQ_NONE;
	}

	BUG_ON(entered++);

	last_status = status;
	status = via[B] & (ST_MASK|CTLR_IRQ);

	switch (macii_state) {
		case idle:
			if (reading_reply) {
				reply_ptr = current_req->reply;
			} else {
				BUG_ON(current_req != NULL);
				reply_ptr = reply_buf;
			}

			x = via[SR];

			if ((status & CTLR_IRQ) && (x == 0xFF)) {
				/* Bus timeout without SRQ sequence:
				 *     data is "FF" while CTLR_IRQ is "H"
				 */
				reply_len = 0;
				srq_asserted = 0;
				macii_state = read_done;
			} else {
				macii_state = reading;
				*reply_ptr = x;
				reply_len = 1;
			}

			/* set ADB state = even for first data byte */
			via[B] = (via[B] & ~ST_MASK) | ST_EVEN;
			break;

		case sending:
			req = current_req;
			if (data_index >= req->nbytes) {
				req->sent = 1;
				macii_state = idle;

				if (req->reply_expected) {
					reading_reply = 1;
				} else {
					req->complete = 1;
					current_req = req->next;
					if (req->done) (*req->done)(req);

					if (current_req)
						macii_start();
					else
						if (need_autopoll())
							macii_autopoll(autopoll_devs);
				}

				if (macii_state == idle) {
					/* reset to shift in */
					via[ACR] &= ~SR_OUT;
					x = via[SR];
					/* set ADB state idle - might get SRQ */
					via[B] = (via[B] & ~ST_MASK) | ST_IDLE;
				}
			} else {
				via[SR] = req->data[data_index++];

				if ( (via[B] & ST_MASK) == ST_CMD ) {
					/* just sent the command byte, set to EVEN */
					via[B] = (via[B] & ~ST_MASK) | ST_EVEN;
				} else {
					/* invert state bits, toggle ODD/EVEN */
					via[B] ^= ST_MASK;
				}
			}
			break;

		case reading:
			x = via[SR];
			BUG_ON((status & ST_MASK) == ST_CMD ||
			       (status & ST_MASK) == ST_IDLE);

			/* Bus timeout with SRQ sequence:
			 *     data is "XX FF"      while CTLR_IRQ is "L L"
			 * End of packet without SRQ sequence:
			 *     data is "XX...YY 00" while CTLR_IRQ is "L...H L"
			 * End of packet SRQ sequence:
			 *     data is "XX...YY 00" while CTLR_IRQ is "L...L L"
			 * (where XX is the first response byte and
			 * YY is the last byte of valid response data.)
			 */

			srq_asserted = 0;
			if (!(status & CTLR_IRQ)) {
				if (x == 0xFF) {
					if (!(last_status & CTLR_IRQ)) {
						macii_state = read_done;
						reply_len = 0;
						srq_asserted = 1;
					}
				} else if (x == 0x00) {
					macii_state = read_done;
					if (!(last_status & CTLR_IRQ))
						srq_asserted = 1;
				}
			}

			if (macii_state == reading) {
				BUG_ON(reply_len > 15);
				reply_ptr++;
				*reply_ptr = x;
				reply_len++;
			}

			/* invert state bits, toggle ODD/EVEN */
			via[B] ^= ST_MASK;
			break;

		case read_done:
			x = via[SR];

			if (reading_reply) {
				reading_reply = 0;
				req = current_req;
				req->reply_len = reply_len;
				req->complete = 1;
				current_req = req->next;
				if (req->done) (*req->done)(req);
			} else if (reply_len && autopoll_devs)
				adb_input(reply_buf, reply_len, 0);

			macii_state = idle;

			/* SRQ seen before, initiate poll now */
			if (srq_asserted)
				macii_queue_poll();

			if (current_req)
				macii_start();
			else
				if (need_autopoll())
					macii_autopoll(autopoll_devs);

			if (macii_state == idle)
				via[B] = (via[B] & ~ST_MASK) | ST_IDLE;
			break;

		default:
		break;
	}

	entered--;
	return IRQ_HANDLED;
}