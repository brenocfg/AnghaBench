#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_INQ_RESULTS_CB ;
struct TYPE_7__ {scalar_t__ mode; scalar_t__ duration; scalar_t__ filter_cond_type; int /*<<< orphan*/  filter_cond; int /*<<< orphan*/  max_resps; } ;
typedef  TYPE_2__ tBTM_INQ_PARMS ;
struct TYPE_6__ {scalar_t__ num_resp; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * p_inq_results_cb; scalar_t__ inq_active; TYPE_1__ inq_cmpl_info; scalar_t__ per_max_delay; scalar_t__ per_min_delay; TYPE_2__ inqparms; scalar_t__ inqfilt_active; } ;
typedef  TYPE_3__ tBTM_INQUIRY_VAR_ST ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_9__ {TYPE_3__ btm_inq_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BUSY ; 
 scalar_t__ BTM_CLR_INQUIRY_FILTER ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 scalar_t__ BTM_GENERAL_INQUIRY ; 
 int BTM_GENERAL_INQUIRY_ACTIVE ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_INQ_CLR_FILT_STATE ; 
 int /*<<< orphan*/  BTM_INQ_INACTIVE_STATE ; 
 int /*<<< orphan*/  BTM_INQ_SET_FILT_STATE ; 
 int /*<<< orphan*/  BTM_IsDeviceUp () ; 
 scalar_t__ BTM_LIMITED_INQUIRY ; 
 int BTM_LIMITED_INQUIRY_ACTIVE ; 
 scalar_t__ BTM_MAX_INQUIRY_LENGTH ; 
 scalar_t__ BTM_MIN_INQUIRY_LEN ; 
 int BTM_PERIODIC_INQUIRY_ACTIVE ; 
 scalar_t__ BTM_PER_INQ_MAX_MIN_PERIOD ; 
 scalar_t__ BTM_PER_INQ_MIN_MAX_PERIOD ; 
 scalar_t__ BTM_PER_INQ_MIN_MIN_PERIOD ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  btm_set_inq_event_filter (scalar_t__,int /*<<< orphan*/ *) ; 

tBTM_STATUS BTM_SetPeriodicInquiryMode (tBTM_INQ_PARMS *p_inqparms, UINT16 max_delay,
                                        UINT16 min_delay, tBTM_INQ_RESULTS_CB *p_results_cb)
{
    tBTM_STATUS  status;
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;

    BTM_TRACE_API ("BTM_SetPeriodicInquiryMode: mode: %d, dur: %d, rsps: %d, flt: %d, min: %d, max: %d\n",
                   p_inqparms->mode, p_inqparms->duration, p_inqparms->max_resps,
                   p_inqparms->filter_cond_type, min_delay, max_delay);

    /*** Make sure the device is ready ***/
    if (!BTM_IsDeviceUp()) {
        return (BTM_WRONG_MODE);
    }

    /* Only one active inquiry is allowed in this implementation.
       Also do not allow an inquiry if the inquiry filter is being updated */
    if (p_inq->inq_active || p_inq->inqfilt_active) {
        return (BTM_BUSY);
    }

    /* If illegal parameters return FALSE */
    if (p_inqparms->mode != BTM_GENERAL_INQUIRY &&
            p_inqparms->mode != BTM_LIMITED_INQUIRY) {
        return (BTM_ILLEGAL_VALUE);
    }

    /* Verify the parameters for this command */
    if (p_inqparms->duration < BTM_MIN_INQUIRY_LEN     ||
            p_inqparms->duration > BTM_MAX_INQUIRY_LENGTH  ||
            min_delay <= p_inqparms->duration              ||
            min_delay < BTM_PER_INQ_MIN_MIN_PERIOD         ||
            min_delay > BTM_PER_INQ_MAX_MIN_PERIOD         ||
            max_delay <= min_delay                         ||
            max_delay < BTM_PER_INQ_MIN_MAX_PERIOD)
        /*       max_delay > BTM_PER_INQ_MAX_MAX_PERIOD)*/
        /*  BTM_PER_INQ_MAX_MAX_PERIOD set to 1's in all bits. Condition resulting in false always*/
    {
        return (BTM_ILLEGAL_VALUE);
    }

    /* Save the inquiry parameters to be used upon the completion of setting/clearing the inquiry filter */
    p_inq->inqparms = *p_inqparms;
    p_inq->per_min_delay = min_delay;
    p_inq->per_max_delay = max_delay;
    p_inq->inq_cmpl_info.num_resp = 0;         /* Clear the results counter */
    p_inq->p_inq_results_cb = p_results_cb;

    p_inq->inq_active = (UINT8)((p_inqparms->mode == BTM_LIMITED_INQUIRY) ?
                                (BTM_LIMITED_INQUIRY_ACTIVE | BTM_PERIODIC_INQUIRY_ACTIVE) :
                                (BTM_GENERAL_INQUIRY_ACTIVE | BTM_PERIODIC_INQUIRY_ACTIVE));

    /* If a filter is specified, then save it for later and clear the current filter.
       The setting of the filter is done upon completion of clearing of the previous
       filter.
    */
    if (p_inqparms->filter_cond_type != BTM_CLR_INQUIRY_FILTER) {
        p_inq->state = BTM_INQ_CLR_FILT_STATE;
        p_inqparms->filter_cond_type = BTM_CLR_INQUIRY_FILTER;
    } else { /* The filter is not being used so simply clear it; the inquiry can start after this operation */
        p_inq->state = BTM_INQ_SET_FILT_STATE;
    }

    /* Before beginning the inquiry the current filter must be cleared, so initiate the command */
    if ((status = btm_set_inq_event_filter (p_inqparms->filter_cond_type, &p_inqparms->filter_cond)) != BTM_CMD_STARTED) {
        /* If set filter command is not succesful reset the state */
        p_inq->p_inq_results_cb = NULL;
        p_inq->state = BTM_INQ_INACTIVE_STATE;

    }

    return (status);
}