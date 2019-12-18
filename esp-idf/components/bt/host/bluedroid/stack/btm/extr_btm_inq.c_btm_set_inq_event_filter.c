#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_6__ {int /*<<< orphan*/  dev_class_mask; int /*<<< orphan*/  dev_class; } ;
struct TYPE_8__ {int* bdaddr_cond; TYPE_1__ cod_cond; } ;
typedef  TYPE_3__ tBTM_INQ_FILT_COND ;
typedef  int UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/  inqfilt_active; } ;
struct TYPE_9__ {TYPE_2__ btm_inq_vars; } ;

/* Variables and functions */
#define  BTM_CLR_INQUIRY_FILTER 130 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
#define  BTM_FILTER_COND_BD_ADDR 129 
#define  BTM_FILTER_COND_DEVICE_CLASS 128 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,int,...) ; 
 int DEV_CLASS_LEN ; 
 int /*<<< orphan*/  HCI_FILTER_INQUIRY_RESULT ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ btm_cb ; 
 scalar_t__ btsnd_hcic_set_event_filter (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tBTM_STATUS btm_set_inq_event_filter (UINT8 filter_cond_type,
        tBTM_INQ_FILT_COND *p_filt_cond)
{
    UINT8    condition_length = DEV_CLASS_LEN * 2;
    UINT8    condition_buf[DEV_CLASS_LEN * 2];
    UINT8   *p_cond = condition_buf;                    /* points to the condition to pass to HCI */

#if (BTM_INQ_DEBUG == TRUE)
    BTM_TRACE_DEBUG ("btm_set_inq_event_filter: filter type %d [Clear-0, COD-1, BDADDR-2]\n",
                     filter_cond_type);
    BTM_TRACE_DEBUG ("                       condition [%02x%02x%02x %02x%02x%02x]\n",
                     p_filt_cond->bdaddr_cond[0], p_filt_cond->bdaddr_cond[1], p_filt_cond->bdaddr_cond[2],
                     p_filt_cond->bdaddr_cond[3], p_filt_cond->bdaddr_cond[4], p_filt_cond->bdaddr_cond[5]);
#endif

    /* Load the correct filter condition to pass to the lower layer */
    switch (filter_cond_type) {
    case BTM_FILTER_COND_DEVICE_CLASS:
        /* copy the device class and device class fields into contiguous memory to send to HCI */
        memcpy (condition_buf, p_filt_cond->cod_cond.dev_class, DEV_CLASS_LEN);
        memcpy (&condition_buf[DEV_CLASS_LEN],
                p_filt_cond->cod_cond.dev_class_mask, DEV_CLASS_LEN);

        /* condition length should already be set as the default */
        break;

    case BTM_FILTER_COND_BD_ADDR:
        p_cond = p_filt_cond->bdaddr_cond;

        /* condition length should already be set as the default */
        break;

    case BTM_CLR_INQUIRY_FILTER:
        condition_length = 0;
        break;

    default:
        return (BTM_ILLEGAL_VALUE);     /* Bad parameter was passed in */
    }

    btm_cb.btm_inq_vars.inqfilt_active = TRUE;

    /* Filter the inquiry results for the specified condition type and value */
    if (btsnd_hcic_set_event_filter(HCI_FILTER_INQUIRY_RESULT, filter_cond_type,
                                    p_cond, condition_length))

    {
        return (BTM_CMD_STARTED);
    } else {
        return (BTM_NO_RESOURCES);
    }
}