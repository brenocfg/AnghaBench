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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {scalar_t__ inq_scan_type; } ;
struct TYPE_6__ {TYPE_1__ btm_inq_vars; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* supports_interlaced_inquiry_scan ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 scalar_t__ BTM_IsDeviceUp () ; 
 int /*<<< orphan*/  BTM_MODE_UNSUPPORTED ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 scalar_t__ BTM_SCAN_TYPE_INTERLACED ; 
 scalar_t__ BTM_SCAN_TYPE_STANDARD ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*) ; 
 int /*<<< orphan*/  BTM_WRONG_MODE ; 
 TYPE_3__ btm_cb ; 
 scalar_t__ btsnd_hcic_write_inqscan_type (int /*<<< orphan*/ ) ; 
 TYPE_2__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS BTM_SetInquiryScanType (UINT16 scan_type)
{

    BTM_TRACE_API ("BTM_SetInquiryScanType\n");
    if (scan_type != BTM_SCAN_TYPE_STANDARD && scan_type != BTM_SCAN_TYPE_INTERLACED) {
        return (BTM_ILLEGAL_VALUE);
    }

    /* whatever app wants if device is not 1.2 scan type should be STANDARD */
    if (!controller_get_interface()->supports_interlaced_inquiry_scan()) {
        return (BTM_MODE_UNSUPPORTED);
    }

    /* Check for scan type if configuration has been changed */
    if (scan_type != btm_cb.btm_inq_vars.inq_scan_type) {
        if (BTM_IsDeviceUp()) {
            if (btsnd_hcic_write_inqscan_type ((UINT8)scan_type)) {
                btm_cb.btm_inq_vars.inq_scan_type = scan_type;
            } else {
                return (BTM_NO_RESOURCES);
            }
        } else {
            return (BTM_WRONG_MODE);
        }
    }
    return (BTM_SUCCESS);
}