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
struct cpuinfo_mips {unsigned int tlbsize; int /*<<< orphan*/  options; int /*<<< orphan*/  ases; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_ASE_MDMX ; 
 int /*<<< orphan*/  MIPS_ASE_MIPS16 ; 
 unsigned int MIPS_CONF1_CA ; 
 unsigned int MIPS_CONF1_EP ; 
 unsigned int MIPS_CONF1_FP ; 
 unsigned int MIPS_CONF1_MD ; 
 unsigned int MIPS_CONF1_TLBS ; 
 unsigned int MIPS_CONF1_WR ; 
 unsigned int MIPS_CONF_M ; 
 int /*<<< orphan*/  MIPS_CPU_32FPR ; 
 int /*<<< orphan*/  MIPS_CPU_EJTAG ; 
 int /*<<< orphan*/  MIPS_CPU_FPU ; 
 int /*<<< orphan*/  MIPS_CPU_WATCH ; 
 scalar_t__ cpu_has_tlb ; 
 unsigned int read_c0_config1 () ; 

__attribute__((used)) static inline unsigned int decode_config1(struct cpuinfo_mips *c)
{
	unsigned int config1;

	config1 = read_c0_config1();

	if (config1 & MIPS_CONF1_MD)
		c->ases |= MIPS_ASE_MDMX;
	if (config1 & MIPS_CONF1_WR)
		c->options |= MIPS_CPU_WATCH;
	if (config1 & MIPS_CONF1_CA)
		c->ases |= MIPS_ASE_MIPS16;
	if (config1 & MIPS_CONF1_EP)
		c->options |= MIPS_CPU_EJTAG;
	if (config1 & MIPS_CONF1_FP) {
		c->options |= MIPS_CPU_FPU;
		c->options |= MIPS_CPU_32FPR;
	}
	if (cpu_has_tlb)
		c->tlbsize = ((config1 & MIPS_CONF1_TLBS) >> 25) + 1;

	return config1 & MIPS_CONF_M;
}