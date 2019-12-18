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
struct fsl_udc {struct ep_queue_head* ep_qh; } ;
struct TYPE_2__ {int length; int actual; } ;
struct fsl_req {int dtd_count; TYPE_1__ req; struct ep_td_struct* head; } ;
struct ep_td_struct {scalar_t__ next_td_virt; int /*<<< orphan*/  size_ioc_sts; } ;
struct ep_queue_head {int /*<<< orphan*/  size_ioc_int_sts; } ;

/* Variables and functions */
 int DTD_ERROR_MASK ; 
 int DTD_LENGTH_BIT_POS ; 
 int DTD_PACKET_SIZE ; 
 int DTD_STATUS_ACTIVE ; 
 int DTD_STATUS_DATA_BUFF_ERR ; 
 int DTD_STATUS_HALTED ; 
 int DTD_STATUS_TRANSACTION_ERR ; 
 int EILSEQ ; 
 int EPIPE ; 
 int EPROTO ; 
 int /*<<< orphan*/  ERR (char*,int,...) ; 
 int REQ_UNCOMPLETE ; 
 int /*<<< orphan*/  VDBG (char*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_ep_req(struct fsl_udc *udc, int pipe,
		struct fsl_req *curr_req)
{
	struct ep_td_struct *curr_td;
	int	td_complete, actual, remaining_length, j, tmp;
	int	status = 0;
	int	errors = 0;
	struct  ep_queue_head *curr_qh = &udc->ep_qh[pipe];
	int direction = pipe % 2;

	curr_td = curr_req->head;
	td_complete = 0;
	actual = curr_req->req.length;

	for (j = 0; j < curr_req->dtd_count; j++) {
		remaining_length = (le32_to_cpu(curr_td->size_ioc_sts)
					& DTD_PACKET_SIZE)
				>> DTD_LENGTH_BIT_POS;
		actual -= remaining_length;

		if ((errors = le32_to_cpu(curr_td->size_ioc_sts) &
						DTD_ERROR_MASK)) {
			if (errors & DTD_STATUS_HALTED) {
				ERR("dTD error %08x QH=%d\n", errors, pipe);
				/* Clear the errors and Halt condition */
				tmp = le32_to_cpu(curr_qh->size_ioc_int_sts);
				tmp &= ~errors;
				curr_qh->size_ioc_int_sts = cpu_to_le32(tmp);
				status = -EPIPE;
				/* FIXME: continue with next queued TD? */

				break;
			}
			if (errors & DTD_STATUS_DATA_BUFF_ERR) {
				VDBG("Transfer overflow");
				status = -EPROTO;
				break;
			} else if (errors & DTD_STATUS_TRANSACTION_ERR) {
				VDBG("ISO error");
				status = -EILSEQ;
				break;
			} else
				ERR("Unknown error has occured (0x%x)!\n",
					errors);

		} else if (le32_to_cpu(curr_td->size_ioc_sts)
				& DTD_STATUS_ACTIVE) {
			VDBG("Request not complete");
			status = REQ_UNCOMPLETE;
			return status;
		} else if (remaining_length) {
			if (direction) {
				VDBG("Transmit dTD remaining length not zero");
				status = -EPROTO;
				break;
			} else {
				td_complete++;
				break;
			}
		} else {
			td_complete++;
			VDBG("dTD transmitted successful");
		}

		if (j != curr_req->dtd_count - 1)
			curr_td = (struct ep_td_struct *)curr_td->next_td_virt;
	}

	if (status)
		return status;

	curr_req->req.actual = actual;

	return 0;
}