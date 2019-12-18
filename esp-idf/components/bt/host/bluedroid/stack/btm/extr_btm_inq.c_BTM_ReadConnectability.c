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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int /*<<< orphan*/  connectable_mode; int /*<<< orphan*/  page_scan_period; int /*<<< orphan*/  page_scan_window; } ;
struct TYPE_4__ {TYPE_1__ btm_inq_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_API (char*) ; 
 TYPE_2__ btm_cb ; 

UINT16 BTM_ReadConnectability (UINT16 *p_window, UINT16 *p_interval)
{
    BTM_TRACE_API ("BTM_ReadConnectability\n");
    if (p_window) {
        *p_window = btm_cb.btm_inq_vars.page_scan_window;
    }

    if (p_interval) {
        *p_interval = btm_cb.btm_inq_vars.page_scan_period;
    }

    return (btm_cb.btm_inq_vars.connectable_mode);
}