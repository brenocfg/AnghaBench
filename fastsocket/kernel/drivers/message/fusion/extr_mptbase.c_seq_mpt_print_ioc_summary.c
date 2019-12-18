#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct seq_file {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  HardwareAddressLow; } ;
struct TYPE_8__ {int /*<<< orphan*/  Word; } ;
struct TYPE_9__ {int /*<<< orphan*/  NumberOfPorts; TYPE_1__ FWVersion; } ;
struct TYPE_12__ {int /*<<< orphan*/  active; int /*<<< orphan*/  pci_irq; TYPE_4__ lan_cnfg_page1; TYPE_3__* pfacts; int /*<<< orphan*/  req_depth; TYPE_2__ facts; int /*<<< orphan*/  prod_name; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int ProtocolFlags; } ;
typedef  TYPE_5__ MPT_ADAPTER ;

/* Variables and functions */
 int MPI_PORTFACTS_PROTOCOL_LAN ; 
 int /*<<< orphan*/  MPT_FW_REV_MAGIC_ID_STRING ; 
 int /*<<< orphan*/  mpt_get_fw_exp_ver (char*,TYPE_5__*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static void seq_mpt_print_ioc_summary(MPT_ADAPTER *ioc, struct seq_file *m, int showlan)
{
	char expVer[32];

	mpt_get_fw_exp_ver(expVer, ioc);

	/*
	 *  Shorter summary of attached ioc's...
	 */
	seq_printf(m, "%s: %s, %s%08xh%s, Ports=%d, MaxQ=%d",
			ioc->name,
			ioc->prod_name,
			MPT_FW_REV_MAGIC_ID_STRING,	/* "FwRev=" or somesuch */
			ioc->facts.FWVersion.Word,
			expVer,
			ioc->facts.NumberOfPorts,
			ioc->req_depth);

	if (showlan && (ioc->pfacts[0].ProtocolFlags & MPI_PORTFACTS_PROTOCOL_LAN)) {
		u8 *a = (u8*)&ioc->lan_cnfg_page1.HardwareAddressLow;
		seq_printf(m, ", LanAddr=%02X:%02X:%02X:%02X:%02X:%02X",
			a[5], a[4], a[3], a[2], a[1], a[0]);
	}

	seq_printf(m, ", IRQ=%d", ioc->pci_irq);

	if (!ioc->active)
		seq_printf(m, " (disabled)");

	seq_putc(m, '\n');
}