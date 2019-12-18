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
struct pcf50633_mbc {scalar_t__ adapter_active; scalar_t__ adapter_online; scalar_t__ usb_active; scalar_t__ usb_online; } ;
struct pcf50633 {int /*<<< orphan*/  mbc_pdev; } ;

/* Variables and functions */
 int PCF50633_MBC_ADAPTER_ACTIVE ; 
 int PCF50633_MBC_ADAPTER_ONLINE ; 
 int PCF50633_MBC_USB_ACTIVE ; 
 int PCF50633_MBC_USB_ONLINE ; 
 struct pcf50633_mbc* platform_get_drvdata (int /*<<< orphan*/ ) ; 

int pcf50633_mbc_get_status(struct pcf50633 *pcf)
{
	struct pcf50633_mbc *mbc  = platform_get_drvdata(pcf->mbc_pdev);
	int status = 0;

	if (mbc->usb_online)
		status |= PCF50633_MBC_USB_ONLINE;
	if (mbc->usb_active)
		status |= PCF50633_MBC_USB_ACTIVE;
	if (mbc->adapter_online)
		status |= PCF50633_MBC_ADAPTER_ONLINE;
	if (mbc->adapter_active)
		status |= PCF50633_MBC_ADAPTER_ACTIVE;

	return status;
}