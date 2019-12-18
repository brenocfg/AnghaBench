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
struct Host {int Type; int Mode; int Ivec; int /*<<< orphan*/  Control; } ;

/* Variables and functions */
 int BOOT_FROM_RAM ; 
 int EXTERNAL_BUS_ON ; 
 int PCITpBootFromRam ; 
 int PCITpBusEnable ; 
 int* RIOAtVec2Ctrl ; 
#define  RIO_AT 129 
 int /*<<< orphan*/  RIO_DEBUG_BOOT ; 
#define  RIO_PCI 128 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

void rio_start_card_running(struct Host *HostP)
{
	switch (HostP->Type) {
	case RIO_AT:
		rio_dprintk(RIO_DEBUG_BOOT, "Start ISA card running\n");
		writeb(BOOT_FROM_RAM | EXTERNAL_BUS_ON | HostP->Mode | RIOAtVec2Ctrl[HostP->Ivec & 0xF], &HostP->Control);
		break;
	case RIO_PCI:
		/*
		 ** PCI is much the same as MCA. Everything is once again memory
		 ** mapped, so we are writing to memory registers instead of io
		 ** ports.
		 */
		rio_dprintk(RIO_DEBUG_BOOT, "Start PCI card running\n");
		writeb(PCITpBootFromRam | PCITpBusEnable | HostP->Mode, &HostP->Control);
		break;
	default:
		rio_dprintk(RIO_DEBUG_BOOT, "Unknown host type %d\n", HostP->Type);
		break;
	}
	return;
}