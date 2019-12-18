#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_INQ_RESULTS_CB ;
struct TYPE_12__ {int mode; int filter_cond_type; int /*<<< orphan*/  filter_cond; int /*<<< orphan*/  duration; int /*<<< orphan*/ * intl_duration; int /*<<< orphan*/  max_resps; } ;
typedef  TYPE_4__ tBTM_INQ_PARMS ;
struct TYPE_11__ {scalar_t__ num_resp; } ;
struct TYPE_13__ {int inq_active; scalar_t__ scan_type; void* next_state; int /*<<< orphan*/  state; TYPE_4__ inqparms; TYPE_3__ inq_cmpl_info; int /*<<< orphan*/ * p_inq_results_cb; int /*<<< orphan*/ * p_inq_cmpl_cb; int /*<<< orphan*/ * p_inq_ble_results_cb; scalar_t__ inqfilt_active; } ;
typedef  TYPE_5__ tBTM_INQUIRY_VAR_ST ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_9__ {int /*<<< orphan*/  scan_type; } ;
struct TYPE_10__ {TYPE_1__ inq_var; } ;
struct TYPE_15__ {TYPE_2__ ble_ctr_cb; TYPE_5__ btm_inq_vars; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* supports_ble ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BLE_DUPLICATE_ENABLE ; 
 int BTM_BLE_GENERAL_INQUIRY ; 
 int BTM_BLE_INQUIRY_MASK ; 
 int BTM_BLE_LIMITED_INQUIRY ; 
 size_t BTM_BLE_ONE ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_DISABLE ; 
 int /*<<< orphan*/  BTM_BLE_SCAN_MODE_NONE ; 
 size_t BTM_BLE_TWO ; 
 int BTM_BR_INQUIRY_MASK ; 
 void* BTM_BR_ONE ; 
 void* BTM_BR_TWO ; 
 scalar_t__ BTM_BUSY ; 
#define  BTM_CLR_INQUIRY_FILTER 130 
 scalar_t__ BTM_CMD_STARTED ; 
#define  BTM_FILTER_COND_BD_ADDR 129 
#define  BTM_FILTER_COND_DEVICE_CLASS 128 
 void* BTM_FINISH ; 
 int BTM_GENERAL_INQUIRY ; 
 scalar_t__ BTM_ILLEGAL_VALUE ; 
 int BTM_INQUIRY_INACTIVE ; 
 int BTM_INQUIRY_NONE ; 
 int /*<<< orphan*/  BTM_INQ_ACTIVE_STATE ; 
 int /*<<< orphan*/  BTM_INQ_CLR_FILT_STATE ; 
 int /*<<< orphan*/  BTM_INQ_INACTIVE_STATE ; 
 int /*<<< orphan*/  BTM_INQ_SET_FILT_STATE ; 
 int /*<<< orphan*/  BTM_IsDeviceUp () ; 
 int BTM_LIMITED_INQUIRY ; 
 size_t BTM_NO_INTERLEAVING ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 scalar_t__ BTM_WRONG_MODE ; 
 void* INQ_GENERAL ; 
 scalar_t__ INQ_LE_OBSERVE ; 
 scalar_t__ btm_ble_start_inquiry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ btm_cb ; 
 scalar_t__ btm_set_inq_event_filter (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btsnd_hcic_ble_set_scan_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS BTM_StartInquiry (tBTM_INQ_PARMS *p_inqparms, tBTM_INQ_RESULTS_CB *p_results_cb,
                              tBTM_CMPL_CB *p_cmpl_cb)
{
    tBTM_STATUS  status = BTM_CMD_STARTED;
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;

    BTM_TRACE_API ("BTM_StartInquiry: mode: %d, dur: %d, rsps: %d, flt: %d\n",
                   p_inqparms->mode, p_inqparms->duration, p_inqparms->max_resps,
                   p_inqparms->filter_cond_type);

    /* Only one active inquiry is allowed in this implementation.
       Also do not allow an inquiry if the inquiry filter is being updated */
    if (p_inq->inq_active || p_inq->inqfilt_active) {
#if (defined BLE_INCLUDED && BLE_INCLUDED == TRUE)
        /*check if LE observe is already running*/
        if (p_inq->scan_type == INQ_LE_OBSERVE && p_inq->p_inq_ble_results_cb != NULL) {
            BTM_TRACE_API("BTM_StartInquiry: LE observe in progress");
            p_inq->scan_type = INQ_GENERAL;
            p_inq->inq_active = BTM_INQUIRY_INACTIVE;
            btm_cb.ble_ctr_cb.inq_var.scan_type = BTM_BLE_SCAN_MODE_NONE;
            btsnd_hcic_ble_set_scan_enable (BTM_BLE_SCAN_DISABLE, BTM_BLE_DUPLICATE_ENABLE);
        } else
#endif
        {
            return (BTM_BUSY);
            BTM_TRACE_API("BTM_StartInquiry: return BUSY\n");
        }
    } else {
        p_inq->scan_type = INQ_GENERAL;
    }

    /*** Make sure the device is ready ***/
    if (!BTM_IsDeviceUp()) {
        return (BTM_WRONG_MODE);
    }

    if ((p_inqparms->mode & BTM_BR_INQUIRY_MASK) != BTM_GENERAL_INQUIRY &&
            (p_inqparms->mode & BTM_BR_INQUIRY_MASK) != BTM_LIMITED_INQUIRY
#if (BLE_INCLUDED == TRUE)
            && (p_inqparms->mode & BTM_BLE_INQUIRY_MASK) != BTM_BLE_GENERAL_INQUIRY
            && (p_inqparms->mode & BTM_BLE_INQUIRY_MASK) != BTM_BLE_LIMITED_INQUIRY
#endif
       ) {
        return (BTM_ILLEGAL_VALUE);
    }

#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    if (p_inq->next_state == BTM_FINISH) {
        return BTM_ILLEGAL_VALUE;
    }
#endif


    /* Save the inquiry parameters to be used upon the completion of setting/clearing the inquiry filter */
    p_inq->inqparms = *p_inqparms;

    /* Initialize the inquiry variables */
    p_inq->state = BTM_INQ_ACTIVE_STATE;
    p_inq->p_inq_cmpl_cb = p_cmpl_cb;
    p_inq->p_inq_results_cb = p_results_cb;
    p_inq->inq_cmpl_info.num_resp = 0;         /* Clear the results counter */
    p_inq->inq_active = p_inqparms->mode;

    BTM_TRACE_DEBUG("BTM_StartInquiry: p_inq->inq_active = 0x%02x\n", p_inq->inq_active);

    /* interleave scan minimal conditions */
#if (BLE_INCLUDED==TRUE && (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE))

    /* check if both modes are present */
    if ((p_inqparms->mode & BTM_BLE_INQUIRY_MASK) && (p_inqparms->mode & BTM_BR_INQUIRY_MASK)) {
        BTM_TRACE_API("BTM:Interleave Inquiry Mode Set\n");
        p_inqparms->duration = p_inqparms->intl_duration[p_inq->next_state];
        p_inq->inqparms.duration = p_inqparms->duration;
    } else {
        BTM_TRACE_API("BTM:Single Mode: No interleaving, Mode:0x%02x\n", p_inqparms->mode);
        p_inq->next_state = BTM_NO_INTERLEAVING;
    }
#endif



    /* start LE inquiry here if requested */
#if BLE_INCLUDED == TRUE
    if ((p_inqparms->mode & BTM_BLE_INQUIRY_MASK)
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
            && (p_inq->next_state == BTM_BLE_ONE || p_inq->next_state == BTM_BLE_TWO ||
                p_inq->next_state == BTM_NO_INTERLEAVING)
#endif
       )

    {
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
        p_inq->inq_active = (p_inqparms->mode & BTM_BLE_INQUIRY_MASK);
        BTM_TRACE_API("BTM:Starting LE Scan with duration %d and activeMode:0x%02x\n",
                      p_inqparms->duration, (p_inqparms->mode & BTM_BLE_INQUIRY_MASK));
#endif
        if (!controller_get_interface()->supports_ble()) {
            p_inq->inqparms.mode &= ~ BTM_BLE_INQUIRY_MASK;
            status = BTM_ILLEGAL_VALUE;
        }
        /* BLE for now does not support filter condition for inquiry */
        else if ((status = btm_ble_start_inquiry((UINT8)(p_inqparms->mode & BTM_BLE_INQUIRY_MASK),
                           p_inqparms->duration)) != BTM_CMD_STARTED) {
            BTM_TRACE_ERROR("Err Starting LE Inquiry.\n");
            p_inq->inqparms.mode &= ~ BTM_BLE_INQUIRY_MASK;
        }
#if (!defined(BTA_HOST_INTERLEAVE_SEARCH) || BTA_HOST_INTERLEAVE_SEARCH == FALSE)
        p_inqparms->mode &= ~BTM_BLE_INQUIRY_MASK;
#endif

#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
        if (p_inq->next_state == BTM_NO_INTERLEAVING) {
            p_inq->next_state = BTM_FINISH;
        } else {
            BTM_TRACE_API("BTM:Interleaving: started LE scan, Advancing to next state: %d\n",
                          p_inq->next_state + 1);
            p_inq->next_state += 1;
        }
        /* reset next_state if status <> BTM_Started */
        if (status != BTM_CMD_STARTED) {
            p_inq->next_state = BTM_BR_ONE;
        }

        /* if interleave scan..return here */
        return status;
#endif


        BTM_TRACE_DEBUG("BTM_StartInquiry: mode = %02x\n", p_inqparms->mode);
    }
#endif /* end of BLE_INCLUDED */

    /* we're done with this routine if BR/EDR inquiry is not desired. */
    if ((p_inqparms->mode & BTM_BR_INQUIRY_MASK) == BTM_INQUIRY_NONE) {
        return status;
    }

    /* BR/EDR inquiry portion */
#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
    if ((p_inq->next_state == BTM_BR_ONE || p_inq->next_state == BTM_BR_TWO ||
            p_inq->next_state == BTM_NO_INTERLEAVING )) {
        p_inq->inq_active = (p_inqparms->mode & BTM_BR_INQUIRY_MASK);
#endif
        /* If a filter is specified, then save it for later and clear the current filter.
           The setting of the filter is done upon completion of clearing of the previous
           filter.
        */
        switch (p_inqparms->filter_cond_type) {
        case BTM_CLR_INQUIRY_FILTER:
            p_inq->state = BTM_INQ_SET_FILT_STATE;
            break;

        case BTM_FILTER_COND_DEVICE_CLASS:
        case BTM_FILTER_COND_BD_ADDR:
            /* The filter is not being used so simply clear it;
                the inquiry can start after this operation */
            p_inq->state = BTM_INQ_CLR_FILT_STATE;
            p_inqparms->filter_cond_type = BTM_CLR_INQUIRY_FILTER;
            /* =============>>>> adding LE filtering here ????? */
            break;

        default:
            return (BTM_ILLEGAL_VALUE);
        }

        /* Before beginning the inquiry the current filter must be cleared, so initiate the command */
        if ((status = btm_set_inq_event_filter (p_inqparms->filter_cond_type,
                                                &p_inqparms->filter_cond)) != BTM_CMD_STARTED) {
            p_inq->state = BTM_INQ_INACTIVE_STATE;
        }

#if (defined(BTA_HOST_INTERLEAVE_SEARCH) && BTA_HOST_INTERLEAVE_SEARCH == TRUE)
        if (p_inq->next_state == BTM_NO_INTERLEAVING) {
            p_inq->next_state = BTM_FINISH;
        } else {
            BTM_TRACE_API("BTM:Interleaving: Started BTM inq, Advancing to next state: %d\n",
                          p_inq->next_state + 1);
            p_inq->next_state += 1;
        }
    }
    if (status != BTM_CMD_STARTED) {
        /* Some error beginning the scan process.
           Reset the next_state parameter.. Do we need to reset the inq_active also?
        */
        BTM_TRACE_API("BTM:Interleaving: Error in Starting inquiry, status: 0x%02x\n", status);
        p_inq->next_state = BTM_BR_ONE;
    }
#endif


    return (status);
}