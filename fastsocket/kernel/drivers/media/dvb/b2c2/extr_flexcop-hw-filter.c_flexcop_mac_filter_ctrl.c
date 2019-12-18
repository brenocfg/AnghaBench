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
struct flexcop_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_filter_Mode_sig ; 
 int /*<<< orphan*/  ctrl_208 ; 
 int /*<<< orphan*/  flexcop_set_ibi_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void flexcop_mac_filter_ctrl(struct flexcop_device *fc, int onoff)
{
	flexcop_set_ibi_value(ctrl_208, MAC_filter_Mode_sig, onoff);
}