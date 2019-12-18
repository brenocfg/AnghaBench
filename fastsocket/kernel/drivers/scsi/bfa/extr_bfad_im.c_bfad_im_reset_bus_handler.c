#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {char* ptr; int Status; } ;
struct scsi_cmnd {TYPE_2__ SCp; TYPE_1__* device; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; } ;
struct bfad_itnim_s {int dummy; } ;
struct bfad_im_port_s {struct bfad_s* bfad; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;
typedef  enum bfi_tskim_status { ____Placeholder_bfi_tskim_status } bfi_tskim_status ;
struct TYPE_3__ {struct Scsi_Host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ BFA_STATUS_OK ; 
 int BFI_TSKIM_STS_OK ; 
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int FAILED ; 
 int /*<<< orphan*/  IO_DONE_BIT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ MAX_FCP_TARGET ; 
 int SUCCESS ; 
 int /*<<< orphan*/  bfa_log_level ; 
 struct bfad_itnim_s* bfad_get_itnim (struct bfad_im_port_s*,scalar_t__) ; 
 scalar_t__ bfad_im_target_reset_send (struct bfad_s*,struct scsi_cmnd*,struct bfad_itnim_s*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int
bfad_im_reset_bus_handler(struct scsi_cmnd *cmnd)
{
	struct Scsi_Host *shost = cmnd->device->host;
	struct bfad_im_port_s *im_port =
				(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_s         *bfad = im_port->bfad;
	struct bfad_itnim_s   *itnim;
	unsigned long   flags;
	u32        i, rc, err_cnt = 0;
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	enum bfi_tskim_status task_status;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	for (i = 0; i < MAX_FCP_TARGET; i++) {
		itnim = bfad_get_itnim(im_port, i);
		if (itnim) {
			cmnd->SCp.ptr = (char *)&wq;
			rc = bfad_im_target_reset_send(bfad, cmnd, itnim);
			if (rc != BFA_STATUS_OK) {
				err_cnt++;
				continue;
			}

			/* wait target reset to complete */
			spin_unlock_irqrestore(&bfad->bfad_lock, flags);
			wait_event(wq, test_bit(IO_DONE_BIT,
					(unsigned long *)&cmnd->SCp.Status));
			spin_lock_irqsave(&bfad->bfad_lock, flags);

			task_status = cmnd->SCp.Status >> 1;
			if (task_status != BFI_TSKIM_STS_OK) {
				BFA_LOG(KERN_ERR, bfad, bfa_log_level,
					"target reset failure,"
					" status: %d\n", task_status);
				err_cnt++;
			}
		}
	}
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (err_cnt)
		return FAILED;

	return SUCCESS;
}