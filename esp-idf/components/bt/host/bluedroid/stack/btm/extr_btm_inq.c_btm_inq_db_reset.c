#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* tBTM_STATUS ;
struct TYPE_5__ {void* status; } ;
typedef  TYPE_1__ tBTM_REMOTE_DEV_NAME ;
struct TYPE_6__ {scalar_t__ inq_active; int /*<<< orphan*/  connectable_mode; int /*<<< orphan*/  discoverable_mode; void* inq_scan_type; void* page_scan_type; int /*<<< orphan*/ * p_inq_results_cb; scalar_t__ pending_filt_complete_event; int /*<<< orphan*/  state; int /*<<< orphan*/  (* p_inqfilter_cmpl_cb ) (void**) ;void* inqfilt_active; int /*<<< orphan*/  (* p_remname_cmpl_cb ) (TYPE_1__*) ;int /*<<< orphan*/  remname_bda; void* remname_active; int /*<<< orphan*/  rmt_name_timer_ent; int /*<<< orphan*/  (* p_inq_cmpl_cb ) (scalar_t__*) ;int /*<<< orphan*/  inq_timer_ent; } ;
typedef  TYPE_2__ tBTM_INQUIRY_VAR_ST ;
typedef  scalar_t__ UINT8 ;
struct TYPE_7__ {TYPE_2__ btm_inq_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ADDR_LEN ; 
 int /*<<< orphan*/  BTM_BLE_NON_CONNECTABLE ; 
 int /*<<< orphan*/  BTM_BLE_NON_DISCOVERABLE ; 
 void* BTM_DEV_RESET ; 
 scalar_t__ BTM_GENERAL_INQUIRY_ACTIVE ; 
 scalar_t__ BTM_INQUIRY_INACTIVE ; 
 int /*<<< orphan*/  BTM_INQ_INACTIVE_STATE ; 
 scalar_t__ BTM_LIMITED_INQUIRY_ACTIVE ; 
 int /*<<< orphan*/  BTM_NON_CONNECTABLE ; 
 int /*<<< orphan*/  BTM_NON_DISCOVERABLE ; 
 void* BTM_SCAN_TYPE_STANDARD ; 
 void* FALSE ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  btm_clr_inq_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btm_clr_inq_result_flt () ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub3 (void**) ; 

void btm_inq_db_reset (void)
{
    tBTM_REMOTE_DEV_NAME     rem_name;
    tBTM_INQUIRY_VAR_ST     *p_inq = &btm_cb.btm_inq_vars;
    UINT8                    num_responses;
    UINT8                    temp_inq_active;
    tBTM_STATUS              status;

    btu_stop_timer (&p_inq->inq_timer_ent);

    /* If an inquiry or periodic inquiry is active, reset the mode to inactive */
    if (p_inq->inq_active != BTM_INQUIRY_INACTIVE) {
        temp_inq_active = p_inq->inq_active;    /* Save so state can change BEFORE
                                                       callback is called */
        p_inq->inq_active = BTM_INQUIRY_INACTIVE;

        /* If not a periodic inquiry, the complete callback must be called to notify caller */
        if (temp_inq_active == BTM_LIMITED_INQUIRY_ACTIVE ||
                temp_inq_active == BTM_GENERAL_INQUIRY_ACTIVE) {
            if (p_inq->p_inq_cmpl_cb) {
                num_responses = 0;
                (*p_inq->p_inq_cmpl_cb)(&num_responses);
            }
        }
    }

    /* Cancel a remote name request if active, and notify the caller (if waiting) */
    if (p_inq->remname_active ) {
        btu_stop_timer (&p_inq->rmt_name_timer_ent);
        p_inq->remname_active = FALSE;
        memset(p_inq->remname_bda, 0, BD_ADDR_LEN);

        if (p_inq->p_remname_cmpl_cb) {
            rem_name.status = BTM_DEV_RESET;

            (*p_inq->p_remname_cmpl_cb)(&rem_name);
            p_inq->p_remname_cmpl_cb = NULL;
        }
    }

    /* Cancel an inquiry filter request if active, and notify the caller (if waiting) */
    if (p_inq->inqfilt_active) {
        p_inq->inqfilt_active = FALSE;

        if (p_inq->p_inqfilter_cmpl_cb) {
            status = BTM_DEV_RESET;
            (*p_inq->p_inqfilter_cmpl_cb)(&status);
        }
    }

    p_inq->state = BTM_INQ_INACTIVE_STATE;
    p_inq->pending_filt_complete_event = 0;
    p_inq->p_inq_results_cb = NULL;
    btm_clr_inq_db(NULL);   /* Clear out all the entries in the database */
    btm_clr_inq_result_flt();

    p_inq->discoverable_mode = BTM_NON_DISCOVERABLE;
    p_inq->connectable_mode  = BTM_NON_CONNECTABLE;
    p_inq->page_scan_type    = BTM_SCAN_TYPE_STANDARD;
    p_inq->inq_scan_type     = BTM_SCAN_TYPE_STANDARD;

#if BLE_INCLUDED == TRUE
    p_inq->discoverable_mode |= BTM_BLE_NON_DISCOVERABLE;
    p_inq->connectable_mode  |= BTM_BLE_NON_CONNECTABLE;
#endif
    return;
}