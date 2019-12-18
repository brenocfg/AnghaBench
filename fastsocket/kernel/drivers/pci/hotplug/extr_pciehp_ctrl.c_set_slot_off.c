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
struct slot {int dummy; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 scalar_t__ ATTN_LED (struct controller*) ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 scalar_t__ PWR_LED (struct controller*) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pciehp_green_led_off (struct slot*) ; 
 scalar_t__ pciehp_power_off_slot (struct slot*) ; 
 scalar_t__ pciehp_set_attention_status (struct slot*,int) ; 

__attribute__((used)) static void set_slot_off(struct controller *ctrl, struct slot * pslot)
{
	/* turn off slot, turn on Amber LED, turn off Green LED if supported*/
	if (POWER_CTRL(ctrl)) {
		if (pciehp_power_off_slot(pslot)) {
			ctrl_err(ctrl,
				 "Issue of Slot Power Off command failed\n");
			return;
		}
		/*
		 * After turning power off, we must wait for at least 1 second
		 * before taking any action that relies on power having been
		 * removed from the slot/adapter.
		 */
		msleep(1000);
	}

	if (PWR_LED(ctrl))
		pciehp_green_led_off(pslot);

	if (ATTN_LED(ctrl)) {
		if (pciehp_set_attention_status(pslot, 1)) {
			ctrl_err(ctrl,
				 "Issue of Set Attention Led command failed\n");
			return;
		}
	}
}