#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  hfa384x_t ;
typedef  int /*<<< orphan*/  ctlx_usercb_t ;

/* Variables and functions */
 int /*<<< orphan*/  hfa384x_cb_rrid ; 
 int hfa384x_dorrid_async (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

int
hfa384x_drvr_getconfig_async(hfa384x_t *hw,
			     u16 rid, ctlx_usercb_t usercb, void *usercb_data)
{
	return hfa384x_dorrid_async(hw, rid, NULL, 0,
				    hfa384x_cb_rrid, usercb, usercb_data);
}