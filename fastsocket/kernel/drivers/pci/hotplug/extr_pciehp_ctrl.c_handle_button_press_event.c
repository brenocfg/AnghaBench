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
typedef  int /*<<< orphan*/  u8 ;
struct slot {int state; int /*<<< orphan*/  work; struct controller* ctrl; } ;
struct controller {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTN_LED (struct controller*) ; 
#define  BLINKINGOFF_STATE 132 
#define  BLINKINGON_STATE 131 
 int HZ ; 
#define  POWEROFF_STATE 130 
#define  POWERON_STATE 129 
 int /*<<< orphan*/  PWR_LED (struct controller*) ; 
#define  STATIC_STATE 128 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_warn (struct controller*,char*) ; 
 int /*<<< orphan*/  pciehp_get_power_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_green_led_blink (struct slot*) ; 
 int /*<<< orphan*/  pciehp_green_led_off (struct slot*) ; 
 int /*<<< orphan*/  pciehp_green_led_on (struct slot*) ; 
 int /*<<< orphan*/  pciehp_set_attention_status (struct slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  slot_name (struct slot*) ; 
 int /*<<< orphan*/  update_slot_info (struct slot*) ; 

__attribute__((used)) static void handle_button_press_event(struct slot *p_slot)
{
	struct controller *ctrl = p_slot->ctrl;
	u8 getstatus;

	switch (p_slot->state) {
	case STATIC_STATE:
		pciehp_get_power_status(p_slot, &getstatus);
		if (getstatus) {
			p_slot->state = BLINKINGOFF_STATE;
			ctrl_info(ctrl,
				  "PCI slot #%s - powering off due to button "
				  "press.\n", slot_name(p_slot));
		} else {
			p_slot->state = BLINKINGON_STATE;
			ctrl_info(ctrl,
				  "PCI slot #%s - powering on due to button "
				  "press.\n", slot_name(p_slot));
		}
		/* blink green LED and turn off amber */
		if (PWR_LED(ctrl))
			pciehp_green_led_blink(p_slot);
		if (ATTN_LED(ctrl))
			pciehp_set_attention_status(p_slot, 0);

		schedule_delayed_work(&p_slot->work, 5*HZ);
		break;
	case BLINKINGOFF_STATE:
	case BLINKINGON_STATE:
		/*
		 * Cancel if we are still blinking; this means that we
		 * press the attention again before the 5 sec. limit
		 * expires to cancel hot-add or hot-remove
		 */
		ctrl_info(ctrl, "Button cancel on Slot(%s)\n", slot_name(p_slot));
		cancel_delayed_work(&p_slot->work);
		if (p_slot->state == BLINKINGOFF_STATE) {
			if (PWR_LED(ctrl))
				pciehp_green_led_on(p_slot);
		} else {
			if (PWR_LED(ctrl))
				pciehp_green_led_off(p_slot);
		}
		if (ATTN_LED(ctrl))
			pciehp_set_attention_status(p_slot, 0);
		ctrl_info(ctrl, "PCI slot #%s - action canceled "
			  "due to button press\n", slot_name(p_slot));
		p_slot->state = STATIC_STATE;
		break;
	case POWEROFF_STATE:
	case POWERON_STATE:
		/*
		 * Ignore if the slot is on power-on or power-off state;
		 * this means that the previous attention button action
		 * to hot-add or hot-remove is undergoing
		 */
		ctrl_info(ctrl, "Button ignore on Slot(%s)\n", slot_name(p_slot));
		update_slot_info(p_slot);
		break;
	default:
		ctrl_warn(ctrl, "Not a valid state\n");
		break;
	}
}