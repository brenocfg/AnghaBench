#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* operand_types; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int operands; int* types; int /*<<< orphan*/  suffix; TYPE_3__* op; TYPE_1__ tm; } ;
struct TYPE_7__ {TYPE_2__* regs; } ;
struct TYPE_6__ {int /*<<< orphan*/  reg_name; } ;

/* Variables and functions */
 int Acc ; 
 int Reg16 ; 
 int Reg32 ; 
 int Reg8 ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_4__ i ; 
 int /*<<< orphan*/  register_prefix ; 

__attribute__((used)) static int
check_qword_reg (void)
{
  int op;

  for (op = i.operands; --op >= 0; )
    /* Reject eight bit registers, except where the template requires
       them. (eg. movzb)  */
    if ((i.types[op] & Reg8) != 0
	&& (i.tm.operand_types[op] & (Reg16 | Reg32 | Acc)) != 0)
      {
	as_bad (_("`%s%s' not allowed with `%s%c'"),
		register_prefix,
		i.op[op].regs->reg_name,
		i.tm.name,
		i.suffix);
	return 0;
      }
  /* Warn if the e prefix on a general reg is missing.  */
    else if (((i.types[op] & Reg16) != 0
	      || (i.types[op] & Reg32) != 0)
	     && (i.tm.operand_types[op] & (Reg32 | Acc)) != 0)
      {
	/* Prohibit these changes in the 64bit mode, since the
	   lowering is more complicated.  */
	as_bad (_("Incorrect register `%s%s' used with `%c' suffix"),
		register_prefix, i.op[op].regs->reg_name,
		i.suffix);
	return 0;
      }
  return 1;
}