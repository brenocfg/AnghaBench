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
typedef  scalar_t__ tBTM_STATUS ;
struct TYPE_5__ {int mode; int /*<<< orphan*/  filter_cond; int /*<<< orphan*/  filter_cond_type; } ;
struct TYPE_6__ {scalar_t__ state; scalar_t__ inqfilt_active; TYPE_1__ inqparms; int /*<<< orphan*/  inq_active; scalar_t__ pending_filt_complete_event; int /*<<< orphan*/  (* p_inqfilter_cmpl_cb ) (scalar_t__*) ;} ;
typedef  TYPE_2__ tBTM_INQUIRY_VAR_ST ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (scalar_t__*) ;
typedef  scalar_t__ UINT8 ;
struct TYPE_7__ {TYPE_2__ btm_inq_vars; } ;

/* Variables and functions */
 int BTM_BR_INQUIRY_MASK ; 
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_INQUIRY_INACTIVE ; 
 scalar_t__ BTM_INQ_ACTIVE_STATE ; 
 scalar_t__ BTM_INQ_CLR_FILT_STATE ; 
 scalar_t__ BTM_INQ_INACTIVE_STATE ; 
 scalar_t__ BTM_INQ_SET_FILT_STATE ; 
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,scalar_t__) ; 
 void* FALSE ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 scalar_t__ TRUE ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  btm_initiate_inquiry (TYPE_2__*) ; 
 int /*<<< orphan*/  btm_process_inq_complete (scalar_t__,scalar_t__) ; 
 scalar_t__ btm_set_inq_event_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*) ; 

void btm_event_filter_complete (UINT8 *p)
{
    UINT8            hci_status;
    tBTM_STATUS      status;
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;
    tBTM_CMPL_CB   *p_cb = p_inq->p_inqfilter_cmpl_cb;

#if (BTM_INQ_DEBUG == TRUE)
    BTM_TRACE_DEBUG ("btm_event_filter_complete: inq_active:0x%x state:%d inqfilt_active:%d\n",
                     btm_cb.btm_inq_vars.inq_active, btm_cb.btm_inq_vars.state, btm_cb.btm_inq_vars.inqfilt_active);
#endif
    /* If the filter complete event is from an old or cancelled request, ignore it */
    if (p_inq->pending_filt_complete_event) {
        p_inq->pending_filt_complete_event--;
        return;
    }

    /* Only process the inquiry filter; Ignore the connection filter until it
       is used by the upper layers */
    if (p_inq->inqfilt_active == TRUE ) {
        /* Extract the returned status from the buffer */
        STREAM_TO_UINT8 (hci_status, p);
        if (hci_status != HCI_SUCCESS) {
            /* If standalone operation, return the error status; if embedded in the inquiry, continue the inquiry */
            BTM_TRACE_WARNING ("BTM Warning: Set Event Filter Failed (HCI returned 0x%x)\n", hci_status);
            status = BTM_ERR_PROCESSING;
        } else {
            status = BTM_SUCCESS;
        }

        /* If the set filter was initiated externally (via BTM_SetInqEventFilter), call the
           callback function to notify the initiator that it has completed */
        if (p_inq->state == BTM_INQ_INACTIVE_STATE) {
            p_inq->inqfilt_active = FALSE;
            if (p_cb) {
                (*p_cb) (&status);
            }
        } else    /* An inquiry is active (the set filter command was internally generated),
                   process the next state of the process (Set a new filter or start the inquiry). */
        {
            if (status != BTM_SUCCESS) {
                /* Process the inquiry complete (Error Status) */
                btm_process_inq_complete (BTM_ERR_PROCESSING, (UINT8)(p_inq->inqparms.mode & BTM_BR_INQUIRY_MASK));

                /* btm_process_inq_complete() does not restore the following settings on periodic inquiry */
                p_inq->inqfilt_active = FALSE;
                p_inq->inq_active = BTM_INQUIRY_INACTIVE;
                p_inq->state = BTM_INQ_INACTIVE_STATE;

                return;
            }

            /* Check to see if a new filter needs to be set up */
            if (p_inq->state == BTM_INQ_CLR_FILT_STATE) {
                if ((status = btm_set_inq_event_filter (p_inq->inqparms.filter_cond_type, &p_inq->inqparms.filter_cond)) == BTM_CMD_STARTED) {
                    p_inq->state = BTM_INQ_SET_FILT_STATE;
                } else { /* Error setting the filter: Call the initiator's callback function to indicate a failure */
                    p_inq->inqfilt_active = FALSE;

                    /* Process the inquiry complete (Error Status) */
                    btm_process_inq_complete (BTM_ERR_PROCESSING, (UINT8)(p_inq->inqparms.mode & BTM_BR_INQUIRY_MASK));
                }
            } else { /* Initiate the Inquiry or Periodic Inquiry */
                p_inq->state = BTM_INQ_ACTIVE_STATE;
                p_inq->inqfilt_active = FALSE;
                btm_initiate_inquiry (p_inq);
            }
        }
    }
}