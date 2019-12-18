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

/* Variables and functions */
 int /*<<< orphan*/  CGEN_CPU_OPEN_END ; 
 int /*<<< orphan*/  CGEN_CPU_OPEN_ENDIAN ; 
 int /*<<< orphan*/  CGEN_CPU_OPEN_ISAS ; 
 int /*<<< orphan*/  CGEN_CPU_OPEN_MACHS ; 
 int /*<<< orphan*/  CGEN_ENDIAN_BIG ; 
 int /*<<< orphan*/  CGEN_ENDIAN_LITTLE ; 
 int MEP_CONFIG ; 
 int MEP_CPU ; 
 int MEP_OMASK ; 
 int /*<<< orphan*/  bfd_arch_mep ; 
 int /*<<< orphan*/  bfd_default_set_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_private_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgen_set_parse_operand_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_cgen_cpu_desc ; 
 int /*<<< orphan*/  gas_cgen_initialize_saved_fixups_array () ; 
 int library_flag ; 
 int /*<<< orphan*/  mep_cgen_cpu_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mep_cgen_init_asm (int /*<<< orphan*/ ) ; 
 scalar_t__ mep_config_index ; 
 int /*<<< orphan*/  mep_machine () ; 
 int /*<<< orphan*/  mep_parse_operand ; 
 int optbits ; 
 int optbitset ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ target_big_endian ; 

void
md_begin ()
{
  /* Initialize the `cgen' interface.  */

  /* If the user specifies no options, we default to allowing
     everything.  If the user specifies any enabling options, we
     default to allowing only what is specified.  If the user
     specifies only disabling options, we only disable what is
     specified.  If the user specifies options and a config, the
     options modify the config.  */
  if (optbits && mep_config_index == 0)
    MEP_OMASK = optbits;
  else
    MEP_OMASK = (MEP_OMASK & ~optbitset) | optbits;

  /* Set the machine number and endian.  */
  gas_cgen_cpu_desc = mep_cgen_cpu_open (CGEN_CPU_OPEN_MACHS, 0,
					 CGEN_CPU_OPEN_ENDIAN,
					 target_big_endian
					 ? CGEN_ENDIAN_BIG
					 : CGEN_ENDIAN_LITTLE,
					 CGEN_CPU_OPEN_ISAS, 0,
					 CGEN_CPU_OPEN_END);
  mep_cgen_init_asm (gas_cgen_cpu_desc);

  /* This is a callback from cgen to gas to parse operands.  */
  cgen_set_parse_operand_fn (gas_cgen_cpu_desc, mep_parse_operand);

  /* Identify the architecture.  */
  bfd_default_set_arch_mach (stdoutput, bfd_arch_mep, mep_machine ());

  /* Store the configuration number and core.  */
  bfd_set_private_flags (stdoutput, MEP_CPU | MEP_CONFIG | library_flag);

  /* Initialize the array we'll be using to store fixups.  */
  gas_cgen_initialize_saved_fixups_array();
}