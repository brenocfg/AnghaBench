#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcf50633_mbc {int usb_online; int usb_active; int adapter_online; int adapter_active; TYPE_2__* pcf; int /*<<< orphan*/  adapter; int /*<<< orphan*/  usb; int /*<<< orphan*/  charging_restart_work; } ;
struct TYPE_5__ {TYPE_1__* pdata; } ;
struct TYPE_4__ {int charging_restart_interval; int /*<<< orphan*/  (* mbc_event_callback ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int PCF50633_IRQ_ADPINS ; 
 int PCF50633_IRQ_ADPREM ; 
 int PCF50633_IRQ_BATFULL ; 
 int PCF50633_IRQ_USBINS ; 
 int PCF50633_IRQ_USBLIMOFF ; 
 int PCF50633_IRQ_USBLIMON ; 
 int PCF50633_IRQ_USBREM ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcf50633_mbc_usb_curlim_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static void
pcf50633_mbc_irq_handler(int irq, void *data)
{
	struct pcf50633_mbc *mbc = data;
	int chg_restart_interval =
			mbc->pcf->pdata->charging_restart_interval;

	/* USB */
	if (irq == PCF50633_IRQ_USBINS) {
		mbc->usb_online = 1;
	} else if (irq == PCF50633_IRQ_USBREM) {
		mbc->usb_online = 0;
		mbc->usb_active = 0;
		pcf50633_mbc_usb_curlim_set(mbc->pcf, 0);
		cancel_delayed_work_sync(&mbc->charging_restart_work);
	}

	/* Adapter */
	if (irq == PCF50633_IRQ_ADPINS) {
		mbc->adapter_online = 1;
		mbc->adapter_active = 1;
	} else if (irq == PCF50633_IRQ_ADPREM) {
		mbc->adapter_online = 0;
		mbc->adapter_active = 0;
	}

	if (irq == PCF50633_IRQ_BATFULL) {
		mbc->usb_active = 0;
		mbc->adapter_active = 0;

		if (chg_restart_interval > 0)
			schedule_delayed_work(&mbc->charging_restart_work,
							chg_restart_interval);
	} else if (irq == PCF50633_IRQ_USBLIMON)
		mbc->usb_active = 0;
	else if (irq == PCF50633_IRQ_USBLIMOFF)
		mbc->usb_active = 1;

	power_supply_changed(&mbc->usb);
	power_supply_changed(&mbc->adapter);

	if (mbc->pcf->pdata->mbc_event_callback)
		mbc->pcf->pdata->mbc_event_callback(mbc->pcf, irq);
}