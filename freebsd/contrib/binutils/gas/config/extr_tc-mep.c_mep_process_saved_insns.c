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
struct TYPE_2__ {int /*<<< orphan*/  fields; int /*<<< orphan*/  buffer; int /*<<< orphan*/  insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGEN_FIELDS_BITSIZE (int /*<<< orphan*/ *) ; 
 int MAX_SAVED_FIXUP_CHAINS ; 
 int /*<<< orphan*/  gas_cgen_finish_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gas_cgen_initialize_saved_fixups_array () ; 
 int /*<<< orphan*/  gas_cgen_restore_fixups (int) ; 
 int /*<<< orphan*/  gas_cgen_save_fixups (int) ; 
 int /*<<< orphan*/  listing_prev_line () ; 
 int /*<<< orphan*/  mep_check_parallel_scheduling () ; 
 int num_insns_saved ; 
 TYPE_1__* saved_insns ; 

__attribute__((used)) static void
mep_process_saved_insns (void)
{
  int i;

  gas_cgen_save_fixups (MAX_SAVED_FIXUP_CHAINS - 1);

  /* We have to check for valid scheduling here. */
  mep_check_parallel_scheduling ();

  /* If the last call didn't cause assembly to terminate, we have
     a valid vliw insn/insn pair saved. Restore this instructions'
     fixups and process the insns. */
  for (i = 0;i<num_insns_saved;i++)
    {
      gas_cgen_restore_fixups (i);
      gas_cgen_finish_insn (saved_insns[i].insn, saved_insns[i].buffer,
			    CGEN_FIELDS_BITSIZE (& saved_insns[i].fields),
			    1, NULL);
    }
  gas_cgen_restore_fixups (MAX_SAVED_FIXUP_CHAINS - 1);

  /* Clear the fixups and reset the number insn saved to 0. */
  gas_cgen_initialize_saved_fixups_array ();
  num_insns_saved = 0;
  listing_prev_line ();
}