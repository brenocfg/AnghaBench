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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OOB_CMD_DRIVER_STOP ; 
 int /*<<< orphan*/  rtl8168_oob_notify (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_msleep_loop_wait_low (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rtl_ocp_read_cond ; 

__attribute__((used)) static void rtl8168_driver_stop(struct rtl8169_private *tp)
{
	rtl8168_oob_notify(tp, OOB_CMD_DRIVER_STOP);

	rtl_msleep_loop_wait_low(tp, &rtl_ocp_read_cond, 10, 10);
}