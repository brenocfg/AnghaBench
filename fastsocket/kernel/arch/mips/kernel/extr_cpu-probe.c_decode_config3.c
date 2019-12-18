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
struct cpuinfo_mips {int /*<<< orphan*/  options; int /*<<< orphan*/  ases; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_ASE_DSP ; 
 int /*<<< orphan*/  MIPS_ASE_MIPSMT ; 
 int /*<<< orphan*/  MIPS_ASE_SMARTMIPS ; 
 unsigned int MIPS_CONF3_DSP ; 
 unsigned int MIPS_CONF3_MT ; 
 unsigned int MIPS_CONF3_SM ; 
 unsigned int MIPS_CONF3_ULRI ; 
 unsigned int MIPS_CONF3_VEIC ; 
 unsigned int MIPS_CONF3_VINT ; 
 unsigned int MIPS_CONF_M ; 
 int /*<<< orphan*/  MIPS_CPU_ULRI ; 
 int /*<<< orphan*/  MIPS_CPU_VEIC ; 
 int /*<<< orphan*/  MIPS_CPU_VINT ; 
 unsigned int read_c0_config3 () ; 

__attribute__((used)) static inline unsigned int decode_config3(struct cpuinfo_mips *c)
{
	unsigned int config3;

	config3 = read_c0_config3();

	if (config3 & MIPS_CONF3_SM)
		c->ases |= MIPS_ASE_SMARTMIPS;
	if (config3 & MIPS_CONF3_DSP)
		c->ases |= MIPS_ASE_DSP;
	if (config3 & MIPS_CONF3_VINT)
		c->options |= MIPS_CPU_VINT;
	if (config3 & MIPS_CONF3_VEIC)
		c->options |= MIPS_CPU_VEIC;
	if (config3 & MIPS_CONF3_MT)
	        c->ases |= MIPS_ASE_MIPSMT;
	if (config3 & MIPS_CONF3_ULRI)
		c->options |= MIPS_CPU_ULRI;

	return config3 & MIPS_CONF_M;
}