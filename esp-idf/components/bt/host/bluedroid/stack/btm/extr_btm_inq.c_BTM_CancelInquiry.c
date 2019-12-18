#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_INQ_RESULTS_CB ;
struct TYPE_4__ {int mode; } ;
struct TYPE_5__ {int inq_active; int /*<<< orphan*/  inq_counter; TYPE_1__ inqparms; int /*<<< orphan*/  pending_filt_complete_event; scalar_t__ inqfilt_active; int /*<<< orphan*/ * p_inq_cmpl_cb; int /*<<< orphan*/ * p_inq_results_cb; int /*<<< orphan*/  state; } ;
typedef  TYPE_2__ tBTM_INQUIRY_VAR_ST ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
typedef  int UINT8 ;
struct TYPE_6__ {TYPE_2__ btm_inq_vars; } ;

/* Variables and functions */
 int BTM_BLE_INQUIRY_MASK ; 
 int BTM_BLE_INQ_ACTIVE_MASK ; 
 int BTM_BR_INQUIRY_MASK ; 
 int BTM_INQUIRY_ACTIVE_MASK ; 
 int BTM_INQUIRY_INACTIVE ; 
 int /*<<< orphan*/  BTM_INQ_INACTIVE_STATE ; 
 int /*<<< orphan*/  BTM_IsDeviceUp () ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int BTM_PERIODIC_INQUIRY_ACTIVE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  btm_ble_stop_inquiry () ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btm_clr_inq_result_flt () ; 
 int /*<<< orphan*/  btsnd_hcic_inq_cancel () ; 

tBTM_STATUS BTM_CancelInquiry(void)
{
    tBTM_STATUS           status = BTM_SUCCESS;
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    UINT8 active_mode = p_inq->inq_active;
#endif
    BTM_TRACE_API ("BTM_CancelInquiry called\n");

    /*** Make sure the device is ready ***/
    if (!BTM_IsDeviceUp()) {
        return (BTM_WRONG_MODE);
    }

    /* Only cancel if not in periodic mode, otherwise the caller should call BTM_CancelPeriodicMode */
    if ((p_inq->inq_active & BTM_INQUIRY_ACTIVE_MASK) != 0 &&
            (!(p_inq->inq_active & BTM_PERIODIC_INQUIRY_ACTIVE))) {
        p_inq->inq_active = BTM_INQUIRY_INACTIVE;
        p_inq->state = BTM_INQ_INACTIVE_STATE;
        p_inq->p_inq_results_cb = (tBTM_INQ_RESULTS_CB *) NULL; /* Do not notify caller anymore */
        p_inq->p_inq_cmpl_cb = (tBTM_CMPL_CB *) NULL;    /* Do not notify caller anymore */

        /* If the event filter is in progress, mark it so that the processing of the return
            event will be ignored */
        if (p_inq->inqfilt_active) {
            p_inq->inqfilt_active = FALSE;
            p_inq->pending_filt_complete_event++;
        }
        /* Initiate the cancel inquiry */
        else {
            if (((p_inq->inqparms.mode & BTM_BR_INQUIRY_MASK) != 0)
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
                    && (active_mode & BTM_BR_INQUIRY_MASK)
#endif
               ) {
                if (!btsnd_hcic_inq_cancel()) {
                    status = BTM_NO_RESOURCES;
                }
            }
#if BLE_INCLUDED == TRUE
            if (((p_inq->inqparms.mode & BTM_BLE_INQUIRY_MASK) != 0)
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
                    && (active_mode & BTM_BLE_INQ_ACTIVE_MASK)
#endif
               ) {
                btm_ble_stop_inquiry();
            }
#endif
        }

        /* Do not send the BUSY_LEVEL event yet. Wait for the cancel_complete event
         * and then send the BUSY_LEVEL event
         * btm_acl_update_busy_level (BTM_BLI_INQ_DONE_EVT);
         */

        p_inq->inq_counter++;
        btm_clr_inq_result_flt();
    }

    return (status);
}