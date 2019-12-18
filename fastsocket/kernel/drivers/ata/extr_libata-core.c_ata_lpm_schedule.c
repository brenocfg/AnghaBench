#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  action; } ;
struct TYPE_4__ {TYPE_1__ eh_info; } ;
struct ata_port {int pm_policy; TYPE_2__ link; } ;
typedef  enum link_pm { ____Placeholder_link_pm } link_pm ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_EHI_NO_AUTOPSY ; 
 int /*<<< orphan*/  ATA_EH_LPM ; 
 int /*<<< orphan*/  ata_port_schedule_eh (struct ata_port*) ; 

void ata_lpm_schedule(struct ata_port *ap, enum link_pm policy)
{
	ap->pm_policy = policy;
	ap->link.eh_info.action |= ATA_EH_LPM;
	ap->link.eh_info.flags |= ATA_EHI_NO_AUTOPSY;
	ata_port_schedule_eh(ap);
}