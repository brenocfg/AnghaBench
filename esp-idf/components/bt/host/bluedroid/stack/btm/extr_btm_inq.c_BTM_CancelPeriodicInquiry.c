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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_INQ_RESULTS_CB ;
struct TYPE_3__ {int inq_active; int /*<<< orphan*/  inq_counter; scalar_t__ inqfilt_active; int /*<<< orphan*/  pending_filt_complete_event; int /*<<< orphan*/ * p_inq_results_cb; } ;
typedef  TYPE_1__ tBTM_INQUIRY_VAR_ST ;
struct TYPE_4__ {TYPE_1__ btm_inq_vars; } ;

/* Variables and functions */
 int BTM_INQUIRY_INACTIVE ; 
 int /*<<< orphan*/  BTM_IsDeviceUp () ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int BTM_PERIODIC_INQUIRY_ACTIVE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 scalar_t__ FALSE ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_exit_per_inq () ; 

tBTM_STATUS BTM_CancelPeriodicInquiry(void)
{
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;
    tBTM_STATUS          status = BTM_SUCCESS;
    BTM_TRACE_API ("BTM_CancelPeriodicInquiry called\n");

    /*** Make sure the device is ready ***/
    if (!BTM_IsDeviceUp()) {
        return (BTM_WRONG_MODE);
    }

    /* Only cancel if one is active */
    if (btm_cb.btm_inq_vars.inq_active & BTM_PERIODIC_INQUIRY_ACTIVE) {
        btm_cb.btm_inq_vars.inq_active = BTM_INQUIRY_INACTIVE;
        btm_cb.btm_inq_vars.p_inq_results_cb = (tBTM_INQ_RESULTS_CB *) NULL;

        if (!btsnd_hcic_exit_per_inq ()) {
            status = BTM_NO_RESOURCES;
        }

        /* If the event filter is in progress, mark it so that the processing of the return
           event will be ignored */
        if (p_inq->inqfilt_active) {
            p_inq->pending_filt_complete_event++;
        }

        p_inq->inqfilt_active = FALSE;
        p_inq->inq_counter++;
    }

    return (status);
}