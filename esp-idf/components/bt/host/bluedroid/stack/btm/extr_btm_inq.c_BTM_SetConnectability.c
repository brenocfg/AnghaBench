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
struct TYPE_4__ {scalar_t__ page_scan_window; scalar_t__ page_scan_period; int discoverable_mode; scalar_t__ connectable_mode; } ;
typedef  TYPE_1__ tBTM_INQUIRY_VAR_ST ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {TYPE_1__ btm_inq_vars; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_is_ready ) () ;} ;

/* Variables and functions */
 scalar_t__ BTM_CONNECTABLE ; 
 scalar_t__ BTM_CONNECTABLE_MASK ; 
 scalar_t__ BTM_DEFAULT_CONN_INTERVAL ; 
 scalar_t__ BTM_DEFAULT_CONN_WINDOW ; 
 int /*<<< orphan*/  BTM_DEV_RESET ; 
 int BTM_DISCOVERABLE_MASK ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 scalar_t__ BTM_NON_CONNECTABLE ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,...) ; 
 int /*<<< orphan*/  HCI_INQUIRY_SCAN_ENABLED ; 
 scalar_t__ HCI_MAX_PAGESCAN_INTERVAL ; 
 scalar_t__ HCI_MAX_PAGESCAN_WINDOW ; 
 scalar_t__ HCI_MIN_PAGESCAN_INTERVAL ; 
 scalar_t__ HCI_MIN_PAGESCAN_WINDOW ; 
 int /*<<< orphan*/  HCI_PAGE_SCAN_ENABLED ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_write_pagescan_cfg (scalar_t__,scalar_t__) ; 
 scalar_t__ btsnd_hcic_write_scan_enable (int /*<<< orphan*/ ) ; 
 TYPE_2__* controller_get_interface () ; 
 int /*<<< orphan*/  stub1 () ; 

tBTM_STATUS BTM_SetConnectability (UINT16 page_mode, UINT16 window, UINT16 interval)
{
    UINT8    scan_mode = 0;
    tBTM_INQUIRY_VAR_ST *p_inq = &btm_cb.btm_inq_vars;

    BTM_TRACE_API ("BTM_SetConnectability\n");

    /*** Check mode parameter ***/
    if (page_mode != BTM_NON_CONNECTABLE && page_mode != BTM_CONNECTABLE) {
        return (BTM_ILLEGAL_VALUE);
    }

    /* Make sure the controller is active */
    if (!controller_get_interface()->get_is_ready()) {
        return (BTM_DEV_RESET);
    }

    /* If the window and/or interval is '0', set to default values */
    if (!window) {
        window = BTM_DEFAULT_CONN_WINDOW;
    }

    if (!interval) {
        interval = BTM_DEFAULT_CONN_INTERVAL;
    }

    BTM_TRACE_API ("BTM_SetConnectability: mode %d [NonConn-0, Conn-1], window 0x%04x, interval 0x%04x\n",
                   page_mode, window, interval);

    /*** Check for valid window and interval parameters ***/
    /*** Only check window and duration if mode is connectable ***/
    if (page_mode == BTM_CONNECTABLE) {
        /* window must be less than or equal to interval */
        if (window < HCI_MIN_PAGESCAN_WINDOW     ||
                window > HCI_MAX_PAGESCAN_WINDOW     ||
                interval < HCI_MIN_PAGESCAN_INTERVAL ||
                interval > HCI_MAX_PAGESCAN_INTERVAL ||
                window > interval) {
            return (BTM_ILLEGAL_VALUE);
        }

        scan_mode |= HCI_PAGE_SCAN_ENABLED;
    }

    if ((window != p_inq->page_scan_window) ||
            (interval != p_inq->page_scan_period)) {
        p_inq->page_scan_window = window;
        p_inq->page_scan_period = interval;
        if (!btsnd_hcic_write_pagescan_cfg (interval, window)) {
            return (BTM_NO_RESOURCES);
        }
    }

    /* Keep the inquiry scan as previouosly set */
    if (p_inq->discoverable_mode & BTM_DISCOVERABLE_MASK) {
        scan_mode |= HCI_INQUIRY_SCAN_ENABLED;
    }

    if (btsnd_hcic_write_scan_enable (scan_mode)) {
        p_inq->connectable_mode &= (~BTM_CONNECTABLE_MASK);
        p_inq->connectable_mode |= page_mode;

        return (BTM_SUCCESS);
    }

    return (BTM_NO_RESOURCES);
}