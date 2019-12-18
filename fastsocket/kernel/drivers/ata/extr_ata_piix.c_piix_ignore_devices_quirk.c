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
struct dmi_system_id {char* ident; int /*<<< orphan*/  matches; } ;
struct ata_host {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_HOST_IGNORE_ATA ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 struct dmi_system_id* dmi_first_match (struct dmi_system_id const*) ; 
 scalar_t__ prefer_ms_hyperv ; 

__attribute__((used)) static void piix_ignore_devices_quirk(struct ata_host *host)
{
#if defined(CONFIG_HYPERV_STORAGE) || defined(CONFIG_HYPERV_STORAGE_MODULE)
	static const struct dmi_system_id ignore_hyperv[] = {
		{
			/* On Hyper-V hypervisors the disks are exposed on
			 * both the emulated SATA controller and on the
			 * paravirtualised drivers.  The CD/DVD devices
			 * are only exposed on the emulated controller.
			 * Request we ignore ATA devices on this host.
			 */
			.ident = "Hyper-V Virtual Machine",
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOR,
						"Microsoft Corporation"),
				DMI_MATCH(DMI_PRODUCT_NAME, "Virtual Machine"),
			},
		},
		{ }	/* terminate list */
	};
	const struct dmi_system_id *dmi = dmi_first_match(ignore_hyperv);

	if (dmi && prefer_ms_hyperv) {
		host->flags |= ATA_HOST_IGNORE_ATA;
		dev_info(host->dev, "%s detected, ATA device ignore set\n",
			dmi->ident);
	}
#endif
}