#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_10__ {scalar_t__ iter_type; int done; TYPE_7__* maydefs; TYPE_5__* mustdefs; TYPE_9__* defs; TYPE_6__* mustkills; TYPE_8__* mayuses; TYPE_3__* vuses; TYPE_4__* uses; } ;
typedef  TYPE_1__ ssa_op_iter ;
struct TYPE_17__ {struct TYPE_17__* next; } ;
struct TYPE_16__ {struct TYPE_16__* next; } ;
struct TYPE_15__ {struct TYPE_15__* next; } ;
struct TYPE_14__ {struct TYPE_14__* next; } ;
struct TYPE_13__ {struct TYPE_13__* next; } ;
struct TYPE_12__ {struct TYPE_12__* next; } ;
struct TYPE_11__ {struct TYPE_11__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_OP (TYPE_9__*) ; 
 int /*<<< orphan*/  MAYDEF_OP (TYPE_8__*) ; 
 int /*<<< orphan*/  MAYDEF_RESULT (TYPE_7__*) ; 
 int /*<<< orphan*/  MUSTDEF_KILL (TYPE_6__*) ; 
 int /*<<< orphan*/  MUSTDEF_RESULT (TYPE_5__*) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  USE_OP (TYPE_4__*) ; 
 int /*<<< orphan*/  VUSE_OP (TYPE_3__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ssa_op_iter_tree ; 

__attribute__((used)) static inline tree
op_iter_next_tree (ssa_op_iter *ptr)
{
  tree val;
#ifdef ENABLE_CHECKING
  gcc_assert (ptr->iter_type == ssa_op_iter_tree);
#endif
  if (ptr->uses)
    {
      val = USE_OP (ptr->uses);
      ptr->uses = ptr->uses->next;
      return val;
    }
  if (ptr->vuses)
    {
      val = VUSE_OP (ptr->vuses);
      ptr->vuses = ptr->vuses->next;
      return val;
    }
  if (ptr->mayuses)
    {
      val = MAYDEF_OP (ptr->mayuses);
      ptr->mayuses = ptr->mayuses->next;
      return val;
    }
  if (ptr->mustkills)
    {
      val = MUSTDEF_KILL (ptr->mustkills);
      ptr->mustkills = ptr->mustkills->next;
      return val;
    }
  if (ptr->defs)
    {
      val = DEF_OP (ptr->defs);
      ptr->defs = ptr->defs->next;
      return val;
    }
  if (ptr->mustdefs)
    {
      val = MUSTDEF_RESULT (ptr->mustdefs);
      ptr->mustdefs = ptr->mustdefs->next;
      return val;
    }
  if (ptr->maydefs)
    {
      val = MAYDEF_RESULT (ptr->maydefs);
      ptr->maydefs = ptr->maydefs->next;
      return val;
    }

  ptr->done = true;
  return NULL_TREE;

}