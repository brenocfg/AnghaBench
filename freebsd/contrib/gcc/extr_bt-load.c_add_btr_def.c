#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct btr_def_s {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  fibheap_t ;
typedef  int /*<<< orphan*/  btr_def_group ;
typedef  TYPE_1__* btr_def ;
typedef  TYPE_2__* basic_block ;
struct TYPE_10__ {int index; } ;
struct TYPE_9__ {int luid; unsigned int btr; int cost; int other_btr_uses_before_def; scalar_t__ group; int /*<<< orphan*/ * live_range; int /*<<< orphan*/ * uses; int /*<<< orphan*/ * next_this_group; int /*<<< orphan*/ * next_this_bb; scalar_t__ other_btr_uses_after_use; scalar_t__ has_ambiguous_use; int /*<<< orphan*/  insn; TYPE_2__* bb; } ;

/* Variables and functions */
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int basic_block_freq (TYPE_2__*) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fibheap_insert (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  find_btr_def_group (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,unsigned int,int,int,char*,int) ; 
 int /*<<< orphan*/  migrate_btrl_obstack ; 
 TYPE_1__* obstack_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static btr_def
add_btr_def (fibheap_t all_btr_defs, basic_block bb, int insn_luid, rtx insn,
	     unsigned int dest_reg, int other_btr_uses_before_def,
	     btr_def_group *all_btr_def_groups)
{
  btr_def this
    = obstack_alloc (&migrate_btrl_obstack, sizeof (struct btr_def_s));
  this->bb = bb;
  this->luid = insn_luid;
  this->insn = insn;
  this->btr = dest_reg;
  this->cost = basic_block_freq (bb);
  this->has_ambiguous_use = 0;
  this->other_btr_uses_before_def = other_btr_uses_before_def;
  this->other_btr_uses_after_use = 0;
  this->next_this_bb = NULL;
  this->next_this_group = NULL;
  this->uses = NULL;
  this->live_range = NULL;
  find_btr_def_group (all_btr_def_groups, this);

  fibheap_insert (all_btr_defs, -this->cost, this);

  if (dump_file)
    fprintf (dump_file,
      "Found target reg definition: sets %u { bb %d, insn %d }%s priority %d\n",
      dest_reg, bb->index, INSN_UID (insn), (this->group ? "" : ":not const"),
      this->cost);

  return this;
}