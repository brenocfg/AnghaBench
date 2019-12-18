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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 unsigned long AT91_SMC_BAT_SELECT ; 
 int /*<<< orphan*/  AT91_SMC_CYCLE (int /*<<< orphan*/  const) ; 
 unsigned long AT91_SMC_EXNWMODE_READY ; 
 int /*<<< orphan*/  AT91_SMC_MODE (int /*<<< orphan*/  const) ; 
 unsigned long AT91_SMC_NCS_RDPULSE_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_NCS_RDSETUP_ (int /*<<< orphan*/ ) ; 
 unsigned long AT91_SMC_NCS_WRPULSE_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_NCS_WRSETUP_ (int /*<<< orphan*/ ) ; 
 unsigned long AT91_SMC_NRDCYCLE_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_NRDPULSE_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_NRDSETUP_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_NWECYCLE_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_NWEPULSE_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_NWESETUP_ (scalar_t__ const) ; 
 int /*<<< orphan*/  AT91_SMC_PULSE (int /*<<< orphan*/  const) ; 
 unsigned long AT91_SMC_READMODE ; 
 int /*<<< orphan*/  AT91_SMC_SETUP (int /*<<< orphan*/  const) ; 
 unsigned long AT91_SMC_TDF_ (scalar_t__ const) ; 
 unsigned long AT91_SMC_WRITEMODE ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void set_smc_timings(const u8 chipselect, const u16 cycle,
			    const u16 setup, const u16 pulse,
			    const u16 data_float, int use_iordy)
{
	unsigned long mode = AT91_SMC_READMODE | AT91_SMC_WRITEMODE |
			     AT91_SMC_BAT_SELECT;

	/* disable or enable waiting for IORDY signal */
	if (use_iordy)
		mode |= AT91_SMC_EXNWMODE_READY;

	/* add data float cycles if needed */
	if (data_float)
		mode |= AT91_SMC_TDF_(data_float);

	at91_sys_write(AT91_SMC_MODE(chipselect), mode);

	/* setup timings in SMC */
	at91_sys_write(AT91_SMC_SETUP(chipselect), AT91_SMC_NWESETUP_(setup) |
						   AT91_SMC_NCS_WRSETUP_(0) |
						   AT91_SMC_NRDSETUP_(setup) |
						   AT91_SMC_NCS_RDSETUP_(0));
	at91_sys_write(AT91_SMC_PULSE(chipselect), AT91_SMC_NWEPULSE_(pulse) |
						   AT91_SMC_NCS_WRPULSE_(cycle) |
						   AT91_SMC_NRDPULSE_(pulse) |
						   AT91_SMC_NCS_RDPULSE_(cycle));
	at91_sys_write(AT91_SMC_CYCLE(chipselect), AT91_SMC_NWECYCLE_(cycle) |
						   AT91_SMC_NRDCYCLE_(cycle));
}