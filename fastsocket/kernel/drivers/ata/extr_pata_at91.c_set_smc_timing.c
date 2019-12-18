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
struct device {int dummy; } ;
struct ata_timing {unsigned long cyc8b; unsigned long setup; unsigned long act8b; unsigned long rec8b; } ;
struct at91_ide_info {int /*<<< orphan*/  cs; int /*<<< orphan*/  mck; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_SMC_CYCLE (int /*<<< orphan*/ ) ; 
 int AT91_SMC_NCS_RDPULSE_ (unsigned long) ; 
 int AT91_SMC_NCS_RDSETUP_ (unsigned long) ; 
 int AT91_SMC_NCS_WRPULSE_ (unsigned long) ; 
 int AT91_SMC_NCS_WRSETUP_ (unsigned long) ; 
 int AT91_SMC_NRDCYCLE_ (unsigned long) ; 
 int AT91_SMC_NRDPULSE_ (unsigned long) ; 
 int AT91_SMC_NRDSETUP_ (unsigned long) ; 
 int AT91_SMC_NWECYCLE_ (unsigned long) ; 
 int AT91_SMC_NWEPULSE_ (unsigned long) ; 
 int AT91_SMC_NWESETUP_ (unsigned long) ; 
 int /*<<< orphan*/  AT91_SMC_PULSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AT91_SMC_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int) ; 
 unsigned long calc_mck_cycles (unsigned long,unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,unsigned long,...) ; 

__attribute__((used)) static void set_smc_timing(struct device *dev,
		struct at91_ide_info *info, const struct ata_timing *ata)
{
	unsigned long read_cycle, write_cycle, active, recover;
	unsigned long nrd_setup, nrd_pulse, nrd_recover;
	unsigned long nwe_setup, nwe_pulse;

	unsigned long ncs_write_setup, ncs_write_pulse;
	unsigned long ncs_read_setup, ncs_read_pulse;

	unsigned long mck_hz;

	read_cycle  = ata->cyc8b;
	nrd_setup   = ata->setup;
	nrd_pulse   = ata->act8b;
	nrd_recover = ata->rec8b;

	mck_hz = clk_get_rate(info->mck);

	read_cycle  = calc_mck_cycles(read_cycle, mck_hz);
	nrd_setup   = calc_mck_cycles(nrd_setup, mck_hz);
	nrd_pulse   = calc_mck_cycles(nrd_pulse, mck_hz);
	nrd_recover = calc_mck_cycles(nrd_recover, mck_hz);

	active  = nrd_setup + nrd_pulse;
	recover = read_cycle - active;

	/* Need at least two cycles recovery */
	if (recover < 2)
		read_cycle = active + 2;

	/* (CS0, CS1, DIR, OE) <= (CFCE1, CFCE2, CFRNW, NCSX) timings */
	ncs_read_setup = 1;
	ncs_read_pulse = read_cycle - 2;

	/* Write timings same as read timings */
	write_cycle = read_cycle;
	nwe_setup = nrd_setup;
	nwe_pulse = nrd_pulse;
	ncs_write_setup = ncs_read_setup;
	ncs_write_pulse = ncs_read_pulse;

	dev_dbg(dev, "ATA timings: nrd_setup = %lu nrd_pulse = %lu nrd_cycle = %lu\n",
			nrd_setup, nrd_pulse, read_cycle);
	dev_dbg(dev, "ATA timings: nwe_setup = %lu nwe_pulse = %lu nwe_cycle = %lu\n",
			nwe_setup, nwe_pulse, write_cycle);
	dev_dbg(dev, "ATA timings: ncs_read_setup = %lu ncs_read_pulse = %lu\n",
			ncs_read_setup, ncs_read_pulse);
	dev_dbg(dev, "ATA timings: ncs_write_setup = %lu ncs_write_pulse = %lu\n",
			ncs_write_setup, ncs_write_pulse);

	at91_sys_write(AT91_SMC_SETUP(info->cs),
			AT91_SMC_NWESETUP_(nwe_setup) |
			AT91_SMC_NRDSETUP_(nrd_setup) |
			AT91_SMC_NCS_WRSETUP_(ncs_write_setup) |
			AT91_SMC_NCS_RDSETUP_(ncs_read_setup));

	at91_sys_write(AT91_SMC_PULSE(info->cs),
			AT91_SMC_NWEPULSE_(nwe_pulse) |
			AT91_SMC_NRDPULSE_(nrd_pulse) |
			AT91_SMC_NCS_WRPULSE_(ncs_write_pulse) |
			AT91_SMC_NCS_RDPULSE_(ncs_read_pulse));

	at91_sys_write(AT91_SMC_CYCLE(info->cs),
			AT91_SMC_NWECYCLE_(write_cycle) |
			AT91_SMC_NRDCYCLE_(read_cycle));

	return;
}