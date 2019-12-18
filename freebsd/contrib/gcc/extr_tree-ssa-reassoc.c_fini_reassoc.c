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
struct TYPE_2__ {int linearized; int constants_eliminated; int ops_eliminated; int rewritten; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 int TDF_STATS ; 
 int /*<<< orphan*/  VEC_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bb_rank ; 
 int /*<<< orphan*/  broken_up_subtracts ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_alloc_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  operand_entry_pool ; 
 int /*<<< orphan*/  operand_rank ; 
 TYPE_1__ reassociate_stats ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void
fini_reassoc (void)
{

  if (dump_file && (dump_flags & TDF_STATS))
    {
      fprintf (dump_file, "Reassociation stats:\n");
      fprintf (dump_file, "Linearized: %d\n", 
	       reassociate_stats.linearized);
      fprintf (dump_file, "Constants eliminated: %d\n",
	       reassociate_stats.constants_eliminated);
      fprintf (dump_file, "Ops eliminated: %d\n",
	       reassociate_stats.ops_eliminated);
      fprintf (dump_file, "Statements rewritten: %d\n",
	       reassociate_stats.rewritten);
    }
  htab_delete (operand_rank);

  free_alloc_pool (operand_entry_pool);
  free (bb_rank);
  VEC_free (tree, heap, broken_up_subtracts);
  free_dominance_info (CDI_POST_DOMINATORS);
}