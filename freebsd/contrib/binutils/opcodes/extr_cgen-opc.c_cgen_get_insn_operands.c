#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum cgen_operand_type { ____Placeholder_cgen_operand_type } cgen_operand_type ;
struct TYPE_9__ {int (* get_int_operand ) (TYPE_3__*,int,int /*<<< orphan*/  const*) ;} ;
struct TYPE_8__ {TYPE_1__* opinst; } ;
struct TYPE_7__ {scalar_t__ type; int op_type; int index; } ;
typedef  TYPE_1__ CGEN_OPINST ;
typedef  TYPE_2__ CGEN_INSN ;
typedef  int /*<<< orphan*/  CGEN_FIELDS ;
typedef  TYPE_3__* CGEN_CPU_DESC ;

/* Variables and functions */
 int CGEN_OPERAND_NIL ; 
 scalar_t__ CGEN_OPINST_END ; 
 int /*<<< orphan*/  abort () ; 
 int stub1 (TYPE_3__*,int,int /*<<< orphan*/  const*) ; 

void
cgen_get_insn_operands (CGEN_CPU_DESC cd,
			const CGEN_INSN *insn,
			const CGEN_FIELDS *fields,
			int *indices)
{
  const CGEN_OPINST *opinst;
  int i;

  if (insn->opinst == NULL)
    abort ();
  for (i = 0, opinst = insn->opinst; opinst->type != CGEN_OPINST_END; ++i, ++opinst)
    {
      enum cgen_operand_type op_type = opinst->op_type;
      if (op_type == CGEN_OPERAND_NIL)
	indices[i] = opinst->index;
      else
	indices[i] = (*cd->get_int_operand) (cd, op_type, fields);
    }
}