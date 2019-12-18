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
typedef  size_t insn_byte_t ;
typedef  int /*<<< orphan*/  const insn_attr_t ;

/* Variables and functions */
 size_t INAT_LSTPFX_MAX ; 
 size_t X86_VEX_M_MAX ; 
 int /*<<< orphan*/  const*** inat_avx_tables ; 

insn_attr_t inat_get_avx_attribute(insn_byte_t opcode, insn_byte_t vex_m,
				   insn_byte_t vex_p)
{
	const insn_attr_t *table;
	if (vex_m > X86_VEX_M_MAX || vex_p > INAT_LSTPFX_MAX)
		return 0;
	table = inat_avx_tables[vex_m][vex_p];
	if (!table)
		return 0;
	return table[opcode];
}