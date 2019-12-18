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
struct smc_timing {scalar_t__ ncs_read_setup; scalar_t__ nrd_setup; scalar_t__ ncs_write_setup; scalar_t__ nwe_setup; scalar_t__ ncs_read_pulse; scalar_t__ nrd_pulse; scalar_t__ ncs_write_pulse; scalar_t__ nwe_pulse; scalar_t__ read_cycle; scalar_t__ write_cycle; scalar_t__ ncs_read_recover; scalar_t__ nrd_recover; scalar_t__ ncs_write_recover; scalar_t__ nwe_recover; } ;
struct smc_config {int ncs_read_setup; int nrd_setup; int ncs_write_setup; int nwe_setup; int ncs_read_pulse; int nrd_pulse; int ncs_write_pulse; int nwe_pulse; int read_cycle; int write_cycle; } ;
struct TYPE_2__ {int /*<<< orphan*/  mck; } ;

/* Variables and functions */
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 TYPE_1__* hsmc ; 
 void* ns2cyc (scalar_t__) ; 

void smc_set_timing(struct smc_config *config,
		    const struct smc_timing *timing)
{
	int recover;
	int cycle;

	unsigned long mul;

	/* Reset all SMC timings */
	config->ncs_read_setup	= 0;
	config->nrd_setup	= 0;
	config->ncs_write_setup	= 0;
	config->nwe_setup	= 0;
	config->ncs_read_pulse	= 0;
	config->nrd_pulse	= 0;
	config->ncs_write_pulse	= 0;
	config->nwe_pulse	= 0;
	config->read_cycle	= 0;
	config->write_cycle	= 0;

	/*
	 * cycles = x / T = x * f
	 *   = ((x * 1000000000) * ((f * 65536) / 1000000000)) / 65536
	 *   = ((x * 1000000000) * (((f / 10000) * 65536) / 100000)) / 65536
	 */
	mul = (clk_get_rate(hsmc->mck) / 10000) << 16;
	mul /= 100000;

#define ns2cyc(x) ((((x) * mul) + 65535) >> 16)

	if (timing->ncs_read_setup > 0)
		config->ncs_read_setup = ns2cyc(timing->ncs_read_setup);

	if (timing->nrd_setup > 0)
		config->nrd_setup = ns2cyc(timing->nrd_setup);

	if (timing->ncs_write_setup > 0)
		config->ncs_write_setup = ns2cyc(timing->ncs_write_setup);

	if (timing->nwe_setup > 0)
		config->nwe_setup = ns2cyc(timing->nwe_setup);

	if (timing->ncs_read_pulse > 0)
		config->ncs_read_pulse = ns2cyc(timing->ncs_read_pulse);

	if (timing->nrd_pulse > 0)
		config->nrd_pulse = ns2cyc(timing->nrd_pulse);

	if (timing->ncs_write_pulse > 0)
		config->ncs_write_pulse = ns2cyc(timing->ncs_write_pulse);

	if (timing->nwe_pulse > 0)
		config->nwe_pulse = ns2cyc(timing->nwe_pulse);

	if (timing->read_cycle > 0)
		config->read_cycle = ns2cyc(timing->read_cycle);

	if (timing->write_cycle > 0)
		config->write_cycle = ns2cyc(timing->write_cycle);

	/* Extend read cycle in needed */
	if (timing->ncs_read_recover > 0)
		recover = ns2cyc(timing->ncs_read_recover);
	else
		recover = 1;

	cycle = config->ncs_read_setup + config->ncs_read_pulse + recover;

	if (config->read_cycle < cycle)
		config->read_cycle = cycle;

	/* Extend read cycle in needed */
	if (timing->nrd_recover > 0)
		recover = ns2cyc(timing->nrd_recover);
	else
		recover = 1;

	cycle = config->nrd_setup + config->nrd_pulse + recover;

	if (config->read_cycle < cycle)
		config->read_cycle = cycle;

	/* Extend write cycle in needed */
	if (timing->ncs_write_recover > 0)
		recover = ns2cyc(timing->ncs_write_recover);
	else
		recover = 1;

	cycle = config->ncs_write_setup + config->ncs_write_pulse + recover;

	if (config->write_cycle < cycle)
		config->write_cycle = cycle;

	/* Extend write cycle in needed */
	if (timing->nwe_recover > 0)
		recover = ns2cyc(timing->nwe_recover);
	else
		recover = 1;

	cycle = config->nwe_setup + config->nwe_pulse + recover;

	if (config->write_cycle < cycle)
		config->write_cycle = cycle;
}