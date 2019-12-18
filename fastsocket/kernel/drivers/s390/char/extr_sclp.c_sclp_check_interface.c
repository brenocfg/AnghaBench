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
struct TYPE_3__ {int response_code; } ;
struct init_sccb {TYPE_1__ header; } ;
struct TYPE_4__ {scalar_t__ status; int /*<<< orphan*/  command; scalar_t__ sccb; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int HZ ; 
 int SCLP_INIT_RETRY ; 
 scalar_t__ SCLP_REQ_DONE ; 
 scalar_t__ SCLP_REQ_RUNNING ; 
 int SCLP_RETRY_INTERVAL ; 
 int /*<<< orphan*/  __sclp_make_init_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sclp_set_request_timer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctl_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext_int_info_hwc ; 
 int register_early_external_interrupt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sclp_check_handler ; 
 int /*<<< orphan*/  sclp_check_timeout ; 
 TYPE_2__ sclp_init_req ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_request_timer ; 
 int /*<<< orphan*/  sclp_running_state ; 
 int /*<<< orphan*/  sclp_running_state_running ; 
 int sclp_service_call (int /*<<< orphan*/ ,struct init_sccb*) ; 
 int /*<<< orphan*/  sclp_sync_wait () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  unregister_early_external_interrupt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sclp_check_interface(void)
{
	struct init_sccb *sccb;
	unsigned long flags;
	int retry;
	int rc;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Prepare init mask command */
	rc = register_early_external_interrupt(0x2401, sclp_check_handler,
					       &ext_int_info_hwc);
	if (rc) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return rc;
	}
	for (retry = 0; retry <= SCLP_INIT_RETRY; retry++) {
		__sclp_make_init_req(0, 0);
		sccb = (struct init_sccb *) sclp_init_req.sccb;
		rc = sclp_service_call(sclp_init_req.command, sccb);
		if (rc == -EIO)
			break;
		sclp_init_req.status = SCLP_REQ_RUNNING;
		sclp_running_state = sclp_running_state_running;
		__sclp_set_request_timer(SCLP_RETRY_INTERVAL * HZ,
					 sclp_check_timeout, 0);
		spin_unlock_irqrestore(&sclp_lock, flags);
		/* Enable service-signal interruption - needs to happen
		 * with IRQs enabled. */
		ctl_set_bit(0, 9);
		/* Wait for signal from interrupt or timeout */
		sclp_sync_wait();
		/* Disable service-signal interruption - needs to happen
		 * with IRQs enabled. */
		ctl_clear_bit(0,9);
		spin_lock_irqsave(&sclp_lock, flags);
		del_timer(&sclp_request_timer);
		if (sclp_init_req.status == SCLP_REQ_DONE &&
		    sccb->header.response_code == 0x20) {
			rc = 0;
			break;
		} else
			rc = -EBUSY;
	}
	unregister_early_external_interrupt(0x2401, sclp_check_handler,
					    &ext_int_info_hwc);
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}