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
typedef  int u32 ;
struct TYPE_2__ {int serror; unsigned int err_mask; unsigned int action; } ;
struct ata_eh_context {TYPE_1__ i; } ;
struct ata_link {int flags; struct ata_eh_context eh_context; } ;

/* Variables and functions */
 unsigned int AC_ERR_ATA_BUS ; 
 unsigned int AC_ERR_HSM ; 
 unsigned int AC_ERR_SYSTEM ; 
 unsigned int ATA_EH_RESET ; 
 int ATA_LFLAG_DISABLED ; 
 int SERR_DATA ; 
 int SERR_DEV_XCHG ; 
 int SERR_INTERNAL ; 
 int SERR_PERSISTENT ; 
 int SERR_PHYRDY_CHG ; 
 int SERR_PROTOCOL ; 
 int /*<<< orphan*/  ata_ehi_hotplugged (TYPE_1__*) ; 
 scalar_t__ ata_is_host_link (struct ata_link*) ; 

__attribute__((used)) static void ata_eh_analyze_serror(struct ata_link *link)
{
	struct ata_eh_context *ehc = &link->eh_context;
	u32 serror = ehc->i.serror;
	unsigned int err_mask = 0, action = 0;
	u32 hotplug_mask;

	if (serror & (SERR_PERSISTENT | SERR_DATA)) {
		err_mask |= AC_ERR_ATA_BUS;
		action |= ATA_EH_RESET;
	}
	if (serror & SERR_PROTOCOL) {
		err_mask |= AC_ERR_HSM;
		action |= ATA_EH_RESET;
	}
	if (serror & SERR_INTERNAL) {
		err_mask |= AC_ERR_SYSTEM;
		action |= ATA_EH_RESET;
	}

	/* Determine whether a hotplug event has occurred.  Both
	 * SError.N/X are considered hotplug events for enabled or
	 * host links.  For disabled PMP links, only N bit is
	 * considered as X bit is left at 1 for link plugging.
	 */
	hotplug_mask = 0;

	if (!(link->flags & ATA_LFLAG_DISABLED) || ata_is_host_link(link))
		hotplug_mask = SERR_PHYRDY_CHG | SERR_DEV_XCHG;
	else
		hotplug_mask = SERR_PHYRDY_CHG;

	if (serror & hotplug_mask)
		ata_ehi_hotplugged(&ehc->i);

	ehc->i.err_mask |= err_mask;
	ehc->i.action |= action;
}