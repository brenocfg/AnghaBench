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
struct request {scalar_t__ sense_len; int /*<<< orphan*/  q; struct hp_sw_dh_data* end_io_data; int /*<<< orphan*/  errors; } ;
struct hp_sw_dh_data {int /*<<< orphan*/ * callback_data; int /*<<< orphan*/  (* callback_fn ) (int /*<<< orphan*/ *,unsigned int) ;scalar_t__ retry_cnt; int /*<<< orphan*/  sense; int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 scalar_t__ COMMAND_COMPLETE ; 
 scalar_t__ DID_OK ; 
 int /*<<< orphan*/  HP_SW_NAME ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned int SCSI_DH_IO ; 
 unsigned int SCSI_DH_OK ; 
 unsigned int SCSI_DH_RETRY ; 
 int /*<<< orphan*/  __blk_put_request (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 scalar_t__ host_byte (int /*<<< orphan*/ ) ; 
 unsigned int hp_sw_start_stop (struct hp_sw_dh_data*) ; 
 scalar_t__ msg_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int start_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void start_stop_endio(struct request *req, int error)
{
	struct hp_sw_dh_data *h = req->end_io_data;
	unsigned err = SCSI_DH_OK;

	if (error || host_byte(req->errors) != DID_OK ||
			msg_byte(req->errors) != COMMAND_COMPLETE) {
		sdev_printk(KERN_WARNING, h->sdev,
			    "%s: sending start_stop_unit failed with %x\n",
			    HP_SW_NAME, req->errors);
		err = SCSI_DH_IO;
		goto done;
	}

	if (req->sense_len > 0) {
		err = start_done(h->sdev, h->sense);
		if (err == SCSI_DH_RETRY) {
			err = SCSI_DH_IO;
			if (--h->retry_cnt) {
				blk_put_request(req);
				err = hp_sw_start_stop(h);
				if (err == SCSI_DH_OK)
					return;
			}
		}
	}
done:
	req->end_io_data = NULL;
	__blk_put_request(req->q, req);
	if (h->callback_fn) {
		h->callback_fn(h->callback_data, err);
		h->callback_fn = h->callback_data = NULL;
	}
	return;

}