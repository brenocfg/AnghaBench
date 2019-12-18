#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct mgsl_icount {int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  rx; } ;
struct TYPE_2__ {struct tty_struct* tty; } ;
struct slgt_info {unsigned int rbuf_current; int rbuf_index; unsigned char ignore_status_mask; unsigned int rbuf_count; int /*<<< orphan*/  rx_timer; int /*<<< orphan*/  device_name; struct slgt_desc* rbufs; struct mgsl_icount icount; TYPE_1__ port; } ;
struct slgt_desc {unsigned char* buf; } ;

/* Variables and functions */
 unsigned char BIT0 ; 
 unsigned char BIT1 ; 
 int /*<<< orphan*/  DBGDATA (struct slgt_info*,unsigned char*,int,char*) ; 
 int /*<<< orphan*/  DBGISR (char*) ; 
 int TTY_FRAME ; 
 int TTY_PARITY ; 
 scalar_t__ desc_complete (struct slgt_desc) ; 
 int desc_count (struct slgt_desc) ; 
 int /*<<< orphan*/  free_rbufs (struct slgt_info*,unsigned int,unsigned int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,int) ; 

__attribute__((used)) static void rx_async(struct slgt_info *info)
{
 	struct tty_struct *tty = info->port.tty;
 	struct mgsl_icount *icount = &info->icount;
	unsigned int start, end;
	unsigned char *p;
	unsigned char status;
	struct slgt_desc *bufs = info->rbufs;
	int i, count;
	int chars = 0;
	int stat;
	unsigned char ch;

	start = end = info->rbuf_current;

	while(desc_complete(bufs[end])) {
		count = desc_count(bufs[end]) - info->rbuf_index;
		p     = bufs[end].buf + info->rbuf_index;

		DBGISR(("%s rx_async count=%d\n", info->device_name, count));
		DBGDATA(info, p, count, "rx");

		for(i=0 ; i < count; i+=2, p+=2) {
			ch = *p;
			icount->rx++;

			stat = 0;

			if ((status = *(p+1) & (BIT1 + BIT0))) {
				if (status & BIT1)
					icount->parity++;
				else if (status & BIT0)
					icount->frame++;
				/* discard char if tty control flags say so */
				if (status & info->ignore_status_mask)
					continue;
				if (status & BIT1)
					stat = TTY_PARITY;
				else if (status & BIT0)
					stat = TTY_FRAME;
			}
			if (tty) {
				tty_insert_flip_char(tty, ch, stat);
				chars++;
			}
		}

		if (i < count) {
			/* receive buffer not completed */
			info->rbuf_index += i;
			mod_timer(&info->rx_timer, jiffies + 1);
			break;
		}

		info->rbuf_index = 0;
		free_rbufs(info, end, end);

		if (++end == info->rbuf_count)
			end = 0;

		/* if entire list searched then no frame available */
		if (end == start)
			break;
	}

	if (tty && chars)
		tty_flip_buffer_push(tty);
}