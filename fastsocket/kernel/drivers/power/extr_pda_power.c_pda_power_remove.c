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
struct platform_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* exit ) (int /*<<< orphan*/ ) ;scalar_t__ is_ac_online; scalar_t__ is_usb_online; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ac_draw ; 
 TYPE_3__* ac_irq ; 
 int /*<<< orphan*/  charger_timer ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otg_put_transceiver (scalar_t__) ; 
 int /*<<< orphan*/  pda_psy_ac ; 
 int /*<<< orphan*/  pda_psy_usb ; 
 TYPE_2__* pdata ; 
 scalar_t__ polling ; 
 int /*<<< orphan*/  polling_timer ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_timer ; 
 scalar_t__ transceiver ; 
 TYPE_1__* usb_irq ; 

__attribute__((used)) static int pda_power_remove(struct platform_device *pdev)
{
	if (pdata->is_usb_online && usb_irq)
		free_irq(usb_irq->start, &pda_psy_usb);
	if (pdata->is_ac_online && ac_irq)
		free_irq(ac_irq->start, &pda_psy_ac);

	if (polling)
		del_timer_sync(&polling_timer);
	del_timer_sync(&charger_timer);
	del_timer_sync(&supply_timer);

	if (pdata->is_usb_online)
		power_supply_unregister(&pda_psy_usb);
	if (pdata->is_ac_online)
		power_supply_unregister(&pda_psy_ac);
#ifdef CONFIG_USB_OTG_UTILS
	if (transceiver)
		otg_put_transceiver(transceiver);
#endif
	if (ac_draw) {
		regulator_put(ac_draw);
		ac_draw = NULL;
	}
	if (pdata->exit)
		pdata->exit(dev);

	return 0;
}