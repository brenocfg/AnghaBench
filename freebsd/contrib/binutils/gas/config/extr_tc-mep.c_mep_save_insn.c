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
typedef  int /*<<< orphan*/  mep_insn ;

/* Variables and functions */
 size_t MAX_SAVED_FIXUP_CHAINS ; 
 int /*<<< orphan*/  as_fatal (char*) ; 
 int /*<<< orphan*/  gas_cgen_save_fixups (size_t) ; 
 size_t num_insns_saved ; 
 int /*<<< orphan*/ * saved_insns ; 

__attribute__((used)) static void
mep_save_insn (mep_insn insn)
{
  /* Consider change MAX_SAVED_FIXUP_CHAINS to MAX_PARALLEL_INSNS. */
  if (num_insns_saved < 0 || num_insns_saved >= MAX_SAVED_FIXUP_CHAINS)
    {
      as_fatal("index into saved_insns[] out of bounds.");
      return;
    }
  saved_insns[num_insns_saved] = insn;
  gas_cgen_save_fixups(num_insns_saved);
  num_insns_saved++;
}