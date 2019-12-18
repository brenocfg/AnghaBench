#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {int /*<<< orphan*/  stream; int /*<<< orphan*/  (* fprintf_func ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_4__ {int nargs; int /*<<< orphan*/ * arg; } ;
typedef  TYPE_1__ ins ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_5__ {int size; } ;

/* Variables and functions */
 scalar_t__ INST_HAS_REG_LIST ; 
 scalar_t__ IS_INSN_MNEMONIC (char*) ; 
 TYPE_3__* instruction ; 
 int /*<<< orphan*/  print_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct disassemble_info*) ; 
 int processing_argument_number ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
print_arguments (ins *currInsn, bfd_vma memaddr, struct disassemble_info *info)
{
  int i;

  /* For "pop/push/popret RA instruction only.  */
  if ((IS_INSN_MNEMONIC ("pop")
       || (IS_INSN_MNEMONIC ("popret")
	   || (IS_INSN_MNEMONIC ("push"))))
      && currInsn->nargs == 1)
    {
      info->fprintf_func (info->stream, "RA");
      return;
    }

  for (i = 0; i < currInsn->nargs; i++)
    {
      processing_argument_number = i;

      /* For "bal (ra), disp17" instruction only.  */
      if ((IS_INSN_MNEMONIC ("bal")) && (i == 0) && instruction->size == 2)
        {
          info->fprintf_func (info->stream, "(ra),");
          continue;
        }

      if ((INST_HAS_REG_LIST) && (i == 2))
        info->fprintf_func (info->stream, "RA");
      else
        print_arg (&currInsn->arg[i], memaddr, info);

      if ((i != currInsn->nargs - 1) && (!IS_INSN_MNEMONIC ("b")))
        info->fprintf_func (info->stream, ",");
    }
}