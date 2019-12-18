#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int nargs; TYPE_1__* arg; } ;
typedef  TYPE_2__ ins ;
struct TYPE_8__ {int /*<<< orphan*/  mnemonic; } ;
struct TYPE_6__ {int /*<<< orphan*/  X_op; int /*<<< orphan*/  constant; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ IS_INSN_MNEMONIC (char*) ; 
 int /*<<< orphan*/  O_constant ; 
 int /*<<< orphan*/  arg_ic ; 
 int /*<<< orphan*/ ** cr16_no_op_insn ; 
 int /*<<< orphan*/  gettrap (char*) ; 
 TYPE_5__* instruction ; 
 int /*<<< orphan*/  parse_operands (TYPE_2__*,char*) ; 
 scalar_t__ streq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_insn (ins *insn, char *operands)
{
  int i;

  /* Handle instructions with no operands.  */
  for (i = 0; cr16_no_op_insn[i] != NULL; i++)
  {
    if (streq (cr16_no_op_insn[i], instruction->mnemonic))
    {
      insn->nargs = 0;
      return;
    }
  }

  /* Handle 'excp' instructions.  */
  if (IS_INSN_MNEMONIC ("excp"))
    {
      insn->nargs = 1;
      insn->arg[0].type = arg_ic;
      insn->arg[0].constant = gettrap (operands);
      insn->arg[0].X_op = O_constant;
      return;
    }

  if (operands != NULL)
    parse_operands (insn, operands);
}