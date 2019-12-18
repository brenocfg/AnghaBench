#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct btr_user_s {int dummy; } ;
typedef  void* rtx ;
typedef  TYPE_1__* btr_user ;
typedef  TYPE_2__* basic_block ;
struct TYPE_7__ {int index; } ;
struct TYPE_6__ {int luid; int first_reaching_def; void* use; scalar_t__ n_reaching_defs; int /*<<< orphan*/ * next; scalar_t__ other_use_this_block; void* insn; TYPE_2__* bb; } ;

/* Variables and functions */
 int INSN_UID (void*) ; 
 void* NULL_RTX ; 
 int /*<<< orphan*/  PATTERN (void*) ; 
 int REGNO (void*) ; 
 int /*<<< orphan*/  btr_referenced_p (int /*<<< orphan*/ ,void**) ; 
 scalar_t__ dump_file ; 
 void** find_btr_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  migrate_btrl_obstack ; 
 TYPE_1__* obstack_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static btr_user
new_btr_user (basic_block bb, int insn_luid, rtx insn)
{
  /* This instruction reads target registers.  We need
     to decide whether we can replace all target register
     uses easily.
   */
  rtx *usep = find_btr_use (PATTERN (insn));
  rtx use;
  btr_user user = NULL;

  if (usep)
    {
      int unambiguous_single_use;

      /* We want to ensure that USE is the only use of a target
	 register in INSN, so that we know that to rewrite INSN to use
	 a different target register, all we have to do is replace USE.  */
      unambiguous_single_use = !btr_referenced_p (PATTERN (insn), usep);
      if (!unambiguous_single_use)
	usep = NULL;
    }
  use = usep ? *usep : NULL_RTX;
  user = obstack_alloc (&migrate_btrl_obstack, sizeof (struct btr_user_s));
  user->bb = bb;
  user->luid = insn_luid;
  user->insn = insn;
  user->use = use;
  user->other_use_this_block = 0;
  user->next = NULL;
  user->n_reaching_defs = 0;
  user->first_reaching_def = -1;

  if (dump_file)
    {
      fprintf (dump_file, "Uses target reg: { bb %d, insn %d }",
	       bb->index, INSN_UID (insn));

      if (user->use)
	fprintf (dump_file, ": unambiguous use of reg %d\n",
		 REGNO (user->use));
    }

  return user;
}