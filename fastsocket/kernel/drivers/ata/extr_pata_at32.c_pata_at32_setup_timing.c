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
struct smc_timing {int /*<<< orphan*/  nrd_recover; int /*<<< orphan*/  nrd_pulse; int /*<<< orphan*/  nrd_setup; int /*<<< orphan*/  read_cycle; } ;
struct smc_config {int nrd_setup; int nrd_pulse; int read_cycle; int ncs_read_setup; int ncs_read_pulse; int write_cycle; int nwe_setup; int nwe_pulse; int ncs_write_setup; int ncs_write_pulse; } ;
struct device {int dummy; } ;
struct ata_timing {int /*<<< orphan*/  rec8b; int /*<<< orphan*/  act8b; int /*<<< orphan*/  setup; int /*<<< orphan*/  cyc8b; } ;
struct at32_ide_info {int /*<<< orphan*/  cs; struct smc_config smc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int,int,...) ; 
 int /*<<< orphan*/  memset (struct smc_timing*,int /*<<< orphan*/ ,int) ; 
 int smc_set_configuration (int /*<<< orphan*/ ,struct smc_config*) ; 
 int /*<<< orphan*/  smc_set_timing (struct smc_config*,struct smc_timing*) ; 

__attribute__((used)) static int pata_at32_setup_timing(struct device *dev,
				  struct at32_ide_info *info,
				  const struct ata_timing *ata)
{
	struct smc_config *smc = &info->smc;
	struct smc_timing timing;

	int active;
	int recover;

	memset(&timing, 0, sizeof(struct smc_timing));

	/* Total cycle time */
	timing.read_cycle  = ata->cyc8b;

	/* DIOR <= CFIOR timings */
	timing.nrd_setup   = ata->setup;
	timing.nrd_pulse   = ata->act8b;
	timing.nrd_recover = ata->rec8b;

	/* Convert nanosecond timing to clock cycles */
	smc_set_timing(smc, &timing);

	/* Add one extra cycle setup due to signal ring */
	smc->nrd_setup = smc->nrd_setup + 1;

	active  = smc->nrd_setup + smc->nrd_pulse;
	recover = smc->read_cycle - active;

	/* Need at least two cycles recovery */
	if (recover < 2)
	  smc->read_cycle = active + 2;

	/* (CS0, CS1, DIR, OE) <= (CFCE1, CFCE2, CFRNW, NCSX) timings */
	smc->ncs_read_setup = 1;
	smc->ncs_read_pulse = smc->read_cycle - 2;

	/* Write timings same as read timings */
	smc->write_cycle = smc->read_cycle;
	smc->nwe_setup = smc->nrd_setup;
	smc->nwe_pulse = smc->nrd_pulse;
	smc->ncs_write_setup = smc->ncs_read_setup;
	smc->ncs_write_pulse = smc->ncs_read_pulse;

	/* Do some debugging output of ATA and SMC timings */
	dev_dbg(dev, "ATA: C=%d S=%d P=%d R=%d\n",
		ata->cyc8b, ata->setup, ata->act8b, ata->rec8b);

	dev_dbg(dev, "SMC: C=%d S=%d P=%d NS=%d NP=%d\n",
		smc->read_cycle, smc->nrd_setup, smc->nrd_pulse,
		smc->ncs_read_setup, smc->ncs_read_pulse);

	/* Finally, configure the SMC */
	return smc_set_configuration(info->cs, smc);
}