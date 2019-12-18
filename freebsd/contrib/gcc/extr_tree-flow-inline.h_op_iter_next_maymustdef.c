#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  use_operand_p ;
struct TYPE_7__ {scalar_t__ iter_type; int done; TYPE_3__* mustkills; TYPE_5__* mayuses; } ;
typedef  TYPE_1__ ssa_op_iter ;
typedef  int /*<<< orphan*/  def_operand_p ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
struct TYPE_8__ {struct TYPE_8__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAYDEF_OP_PTR (TYPE_5__*) ; 
 int /*<<< orphan*/  MAYDEF_RESULT_PTR (TYPE_5__*) ; 
 int /*<<< orphan*/  MUSTDEF_KILL_PTR (TYPE_3__*) ; 
 int /*<<< orphan*/  MUSTDEF_RESULT_PTR (TYPE_3__*) ; 
 int /*<<< orphan*/  NULL_DEF_OPERAND_P ; 
 int /*<<< orphan*/  NULL_USE_OPERAND_P ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ssa_op_iter_maymustdef ; 

__attribute__((used)) static inline void
op_iter_next_maymustdef (use_operand_p *use, def_operand_p *def, 
			 ssa_op_iter *ptr)
{
#ifdef ENABLE_CHECKING
  gcc_assert (ptr->iter_type == ssa_op_iter_maymustdef);
#endif
  if (ptr->mayuses)
    {
      *def = MAYDEF_RESULT_PTR (ptr->mayuses);
      *use = MAYDEF_OP_PTR (ptr->mayuses);
      ptr->mayuses = ptr->mayuses->next;
      return;
    }

  if (ptr->mustkills)
    {
      *def = MUSTDEF_RESULT_PTR (ptr->mustkills);
      *use = MUSTDEF_KILL_PTR (ptr->mustkills);
      ptr->mustkills = ptr->mustkills->next;
      return;
    }

  *def = NULL_DEF_OPERAND_P;
  *use = NULL_USE_OPERAND_P;
  ptr->done = true;
  return;
}