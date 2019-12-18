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
typedef  int /*<<< orphan*/  u32 ;
struct ipw_priv {int config; int status; int /*<<< orphan*/  led_act_off; int /*<<< orphan*/  led_activity_on; } ;

/* Variables and functions */
 int CFG_NO_LED ; 
 int /*<<< orphan*/  IPW_DEBUG_LED (char*,...) ; 
 int /*<<< orphan*/  IPW_EVENT_REG ; 
 int /*<<< orphan*/  LD_TIME_ACT_ON ; 
 int STATUS_LED_ACT_ON ; 
 int STATUS_RF_KILL_MASK ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipw_read_reg32 (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_register_toggle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_write_reg32 (struct ipw_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ipw_led_activity_on(struct ipw_priv *priv)
{
	u32 led;

	if (priv->config & CFG_NO_LED)
		return;

	if (priv->status & STATUS_RF_KILL_MASK)
		return;

	if (!(priv->status & STATUS_LED_ACT_ON)) {
		led = ipw_read_reg32(priv, IPW_EVENT_REG);
		led |= priv->led_activity_on;

		led = ipw_register_toggle(led);

		IPW_DEBUG_LED("Reg: 0x%08X\n", led);
		ipw_write_reg32(priv, IPW_EVENT_REG, led);

		IPW_DEBUG_LED("Activity LED On\n");

		priv->status |= STATUS_LED_ACT_ON;

		cancel_delayed_work(&priv->led_act_off);
		schedule_delayed_work(&priv->led_act_off, LD_TIME_ACT_ON);
	} else {
		/* Reschedule LED off for full time period */
		cancel_delayed_work(&priv->led_act_off);
		schedule_delayed_work(&priv->led_act_off, LD_TIME_ACT_ON);
	}
}