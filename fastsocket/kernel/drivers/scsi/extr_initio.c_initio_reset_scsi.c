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
struct initio_host {int jsint; scalar_t__ addr; } ;

/* Variables and functions */
 int HZ ; 
 int SCSI_RESET_SUCCESS ; 
 int /*<<< orphan*/  TSC_RST_BUS ; 
 int TSS_SCSIRST_INT ; 
 scalar_t__ TUL_SCtrl0 ; 
 scalar_t__ TUL_SInt ; 
 scalar_t__ TUL_SSignal ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  initio_do_pause (int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int initio_reset_scsi(struct initio_host * host, int seconds)
{
	outb(TSC_RST_BUS, host->addr + TUL_SCtrl0);

	while (!((host->jsint = inb(host->addr + TUL_SInt)) & TSS_SCSIRST_INT))
		cpu_relax();

	/* reset tulip chip */
	outb(0, host->addr + TUL_SSignal);

	/* Stall for a while, wait for target's firmware ready,make it 2 sec ! */
	/* SONY 5200 tape drive won't work if only stall for 1 sec */
	/* FIXME: this is a very long busy wait right now */
	initio_do_pause(seconds * HZ);

	inb(host->addr + TUL_SInt);
	return SCSI_RESET_SUCCESS;
}