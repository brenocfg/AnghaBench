#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_info {TYPE_1__* pub; int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  radio_disabled; scalar_t__ hw_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL_RADIO_HW_DISABLE ; 
 scalar_t__ brcms_b_radio_read_hwdisabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboolclr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mboolset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_radio_hwdisable_upd(struct brcms_c_info *wlc)
{
	if (wlc->pub->hw_off)
		return;

	if (brcms_b_radio_read_hwdisabled(wlc->hw))
		mboolset(wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE);
	else
		mboolclr(wlc->pub->radio_disabled, WL_RADIO_HW_DISABLE);
}