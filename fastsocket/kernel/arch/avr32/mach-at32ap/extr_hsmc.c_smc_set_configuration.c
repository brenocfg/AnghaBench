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
typedef  int u32 ;
struct smc_config {int bus_width; int nwait_mode; scalar_t__ tdf_mode; scalar_t__ byte_write; scalar_t__ nwe_controlled; scalar_t__ nrd_controlled; scalar_t__ tdf_cycles; scalar_t__ read_cycle; scalar_t__ write_cycle; scalar_t__ ncs_read_pulse; scalar_t__ nrd_pulse; scalar_t__ ncs_write_pulse; scalar_t__ nwe_pulse; scalar_t__ ncs_read_setup; scalar_t__ nrd_setup; scalar_t__ ncs_write_setup; scalar_t__ nwe_setup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAT ; 
 scalar_t__ CYCLE0 ; 
 int /*<<< orphan*/  DBW ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  EXNW_MODE ; 
 int HSMC_BF (int /*<<< orphan*/ ,scalar_t__) ; 
 int HSMC_BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ HSMC_DBW_16_BITS ; 
 scalar_t__ HSMC_DBW_32_BITS ; 
 scalar_t__ HSMC_DBW_8_BITS ; 
 scalar_t__ HSMC_EXNW_MODE_DISABLED ; 
 scalar_t__ HSMC_EXNW_MODE_FROZEN ; 
 scalar_t__ HSMC_EXNW_MODE_READY ; 
 scalar_t__ HSMC_EXNW_MODE_RESERVED ; 
 scalar_t__ MODE0 ; 
 int /*<<< orphan*/  NCS_RD_PULSE ; 
 int /*<<< orphan*/  NCS_RD_SETUP ; 
 int /*<<< orphan*/  NCS_WR_PULSE ; 
 int /*<<< orphan*/  NCS_WR_SETUP ; 
 int /*<<< orphan*/  NRD_CYCLE ; 
 int /*<<< orphan*/  NRD_PULSE ; 
 int /*<<< orphan*/  NRD_SETUP ; 
 int NR_CHIP_SELECTS ; 
 int /*<<< orphan*/  NWE_CYCLE ; 
 int /*<<< orphan*/  NWE_PULSE ; 
 int /*<<< orphan*/  NWE_SETUP ; 
 scalar_t__ PULSE0 ; 
 int /*<<< orphan*/  READ_MODE ; 
 scalar_t__ SETUP0 ; 
 int /*<<< orphan*/  TDF_CYCLES ; 
 int /*<<< orphan*/  TDF_MODE ; 
 int /*<<< orphan*/  WRITE_MODE ; 
 int /*<<< orphan*/  hsmc ; 
 int /*<<< orphan*/  hsmc_readl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hsmc_writel (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int,int,int) ; 

int smc_set_configuration(int cs, const struct smc_config *config)
{
	unsigned long offset;
	u32 setup, pulse, cycle, mode;

	if (!hsmc)
		return -ENODEV;
	if (cs >= NR_CHIP_SELECTS)
		return -EINVAL;

	setup = (HSMC_BF(NWE_SETUP, config->nwe_setup)
		 | HSMC_BF(NCS_WR_SETUP, config->ncs_write_setup)
		 | HSMC_BF(NRD_SETUP, config->nrd_setup)
		 | HSMC_BF(NCS_RD_SETUP, config->ncs_read_setup));
	pulse = (HSMC_BF(NWE_PULSE, config->nwe_pulse)
		 | HSMC_BF(NCS_WR_PULSE, config->ncs_write_pulse)
		 | HSMC_BF(NRD_PULSE, config->nrd_pulse)
		 | HSMC_BF(NCS_RD_PULSE, config->ncs_read_pulse));
	cycle = (HSMC_BF(NWE_CYCLE, config->write_cycle)
		 | HSMC_BF(NRD_CYCLE, config->read_cycle));

	switch (config->bus_width) {
	case 1:
		mode = HSMC_BF(DBW, HSMC_DBW_8_BITS);
		break;
	case 2:
		mode = HSMC_BF(DBW, HSMC_DBW_16_BITS);
		break;
	case 4:
		mode = HSMC_BF(DBW, HSMC_DBW_32_BITS);
		break;
	default:
		return -EINVAL;
	}

	switch (config->nwait_mode) {
	case 0:
		mode |= HSMC_BF(EXNW_MODE, HSMC_EXNW_MODE_DISABLED);
		break;
	case 1:
		mode |= HSMC_BF(EXNW_MODE, HSMC_EXNW_MODE_RESERVED);
		break;
	case 2:
		mode |= HSMC_BF(EXNW_MODE, HSMC_EXNW_MODE_FROZEN);
		break;
	case 3:
		mode |= HSMC_BF(EXNW_MODE, HSMC_EXNW_MODE_READY);
		break;
	default:
		return -EINVAL;
	}

	if (config->tdf_cycles) {
		mode |= HSMC_BF(TDF_CYCLES, config->tdf_cycles);
	}

	if (config->nrd_controlled)
		mode |= HSMC_BIT(READ_MODE);
	if (config->nwe_controlled)
		mode |= HSMC_BIT(WRITE_MODE);
	if (config->byte_write)
		mode |= HSMC_BIT(BAT);
	if (config->tdf_mode)
		mode |= HSMC_BIT(TDF_MODE);

	pr_debug("smc cs%d: setup/%08x pulse/%08x cycle/%08x mode/%08x\n",
		 cs, setup, pulse, cycle, mode);

	offset = cs * 0x10;
	hsmc_writel(hsmc, SETUP0 + offset, setup);
	hsmc_writel(hsmc, PULSE0 + offset, pulse);
	hsmc_writel(hsmc, CYCLE0 + offset, cycle);
	hsmc_writel(hsmc, MODE0 + offset, mode);
	hsmc_readl(hsmc, MODE0); /* I/O barrier */

	return 0;
}