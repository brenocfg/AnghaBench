#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  (* fprintf_func ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ disassemble_info ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  scalar_t__ CGEN_SYNTAX_CHAR_TYPE ;
typedef  int /*<<< orphan*/  CGEN_SYNTAX ;
typedef  int /*<<< orphan*/  CGEN_INSN ;
typedef  int /*<<< orphan*/  CGEN_FIELDS ;
typedef  int /*<<< orphan*/  CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  CGEN_INIT_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEN_INSN_ATTRS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CGEN_INSN_MNEMONIC (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * CGEN_INSN_SYNTAX (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  CGEN_SYNTAX_CHAR (scalar_t__ const) ; 
 scalar_t__ CGEN_SYNTAX_CHAR_P (scalar_t__ const) ; 
 int /*<<< orphan*/  CGEN_SYNTAX_FIELD (scalar_t__ const) ; 
 scalar_t__ CGEN_SYNTAX_MNEMONIC_P (scalar_t__ const) ; 
 scalar_t__* CGEN_SYNTAX_STRING (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mep_cgen_print_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_insn_normal (CGEN_CPU_DESC cd,
		   void *dis_info,
		   const CGEN_INSN *insn,
		   CGEN_FIELDS *fields,
		   bfd_vma pc,
		   int length)
{
  const CGEN_SYNTAX *syntax = CGEN_INSN_SYNTAX (insn);
  disassemble_info *info = (disassemble_info *) dis_info;
  const CGEN_SYNTAX_CHAR_TYPE *syn;

  CGEN_INIT_PRINT (cd);

  for (syn = CGEN_SYNTAX_STRING (syntax); *syn; ++syn)
    {
      if (CGEN_SYNTAX_MNEMONIC_P (*syn))
	{
	  (*info->fprintf_func) (info->stream, "%s", CGEN_INSN_MNEMONIC (insn));
	  continue;
	}
      if (CGEN_SYNTAX_CHAR_P (*syn))
	{
	  (*info->fprintf_func) (info->stream, "%c", CGEN_SYNTAX_CHAR (*syn));
	  continue;
	}

      /* We have an operand.  */
      mep_cgen_print_operand (cd, CGEN_SYNTAX_FIELD (*syn), info,
				 fields, CGEN_INSN_ATTRS (insn), pc, length);
    }
}