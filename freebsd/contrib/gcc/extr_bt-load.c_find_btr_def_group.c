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
struct btr_def_group_s {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* btr_def_group ;
typedef  TYPE_2__* btr_def ;
struct TYPE_7__ {TYPE_1__* group; struct TYPE_7__* next_this_group; int /*<<< orphan*/  insn; } ;
struct TYPE_6__ {TYPE_2__* members; struct TYPE_6__* next; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ insn_sets_btr_p (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  migrate_btrl_obstack ; 
 TYPE_1__* obstack_alloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
find_btr_def_group (btr_def_group *all_btr_def_groups, btr_def def)
{
  if (insn_sets_btr_p (def->insn, 1, NULL))
    {
      btr_def_group this_group;
      rtx def_src = SET_SRC (single_set (def->insn));

      /* ?? This linear search is an efficiency concern, particularly
	 as the search will almost always fail to find a match.  */
      for (this_group = *all_btr_def_groups;
	   this_group != NULL;
	   this_group = this_group->next)
	if (rtx_equal_p (def_src, this_group->src))
	  break;

      if (!this_group)
	{
	  this_group = obstack_alloc (&migrate_btrl_obstack,
				      sizeof (struct btr_def_group_s));
	  this_group->src = def_src;
	  this_group->members = NULL;
	  this_group->next = *all_btr_def_groups;
	  *all_btr_def_groups = this_group;
	}
      def->group = this_group;
      def->next_this_group = this_group->members;
      this_group->members = def;
    }
  else
    def->group = NULL;
}