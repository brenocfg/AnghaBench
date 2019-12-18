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
struct gdbarch_tdep {scalar_t__ ppc_gp0_regnum; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int insn_d_field (unsigned int) ; 
 scalar_t__ insn_ds_field (unsigned int) ; 
 scalar_t__ ppc64_desc_entry_point (scalar_t__) ; 
 scalar_t__ read_register (scalar_t__) ; 

__attribute__((used)) static CORE_ADDR
ppc64_standard_linkage_target (CORE_ADDR pc, unsigned int *insn)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  /* The address of the function descriptor this linkage function
     references.  */
  CORE_ADDR desc
    = ((CORE_ADDR) read_register (tdep->ppc_gp0_regnum + 2)
       + (insn_d_field (insn[0]) << 16)
       + insn_ds_field (insn[2]));

  /* The first word of the descriptor is the entry point.  Return that.  */
  return ppc64_desc_entry_point (desc);
}