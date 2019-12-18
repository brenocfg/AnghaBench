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
typedef  int /*<<< orphan*/  subsegT ;
typedef  int /*<<< orphan*/  segT ;

/* Variables and functions */
 scalar_t__ REG_TYPE_FIRST ; 
 scalar_t__ REG_TYPE_MAX ; 
 int SEC_DEBUGGING ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 int /*<<< orphan*/  TARGET_ARCH ; 
 scalar_t__ USE_GLOBAL_POINTER_OPT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ all_reg_maps ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_gp_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  build_dependency_insn_hsh () ; 
 int /*<<< orphan*/  build_reg_hsh (scalar_t__) ; 
 int /*<<< orphan*/  build_score_ops_hsh () ; 
 int /*<<< orphan*/ * dependency_insn_hsh ; 
 int /*<<< orphan*/  g_switch_value ; 
 void* hash_new () ; 
 int /*<<< orphan*/  init_dependency_vector () ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  now_subseg ; 
 int /*<<< orphan*/  pdr_seg ; 
 int /*<<< orphan*/ * score_ops_hsh ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  subseg_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subseg_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
md_begin (void)
{
  unsigned int i;
  segT seg;
  subsegT subseg;

  if ((score_ops_hsh = hash_new ()) == NULL)
    as_fatal (_("virtual memory exhausted"));

  build_score_ops_hsh ();

  if ((dependency_insn_hsh = hash_new ()) == NULL)
    as_fatal (_("virtual memory exhausted"));

  build_dependency_insn_hsh ();

  for (i = (int)REG_TYPE_FIRST; i < (int)REG_TYPE_MAX; i++)
    build_reg_hsh (all_reg_maps + i);

  /* Initialize dependency vector.  */
  init_dependency_vector ();

  bfd_set_arch_mach (stdoutput, TARGET_ARCH, 0);
  seg = now_seg;
  subseg = now_subseg;
  pdr_seg = subseg_new (".pdr", (subsegT) 0);
  (void)bfd_set_section_flags (stdoutput, pdr_seg, SEC_READONLY | SEC_RELOC | SEC_DEBUGGING);
  (void)bfd_set_section_alignment (stdoutput, pdr_seg, 2);
  subseg_set (seg, subseg);

  if (USE_GLOBAL_POINTER_OPT)
    bfd_set_gp_size (stdoutput, g_switch_value);
}