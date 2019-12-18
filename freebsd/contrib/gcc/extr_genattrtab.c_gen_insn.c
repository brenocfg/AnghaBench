#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct insn_def {int lineno; int insn_code; int insn_index; int num_alternatives; int vec_idx; int /*<<< orphan*/  def; struct insn_def* next; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  DEFINE_ASM_ATTRIBUTES 130 
#define  DEFINE_INSN 129 
#define  DEFINE_PEEPHOLE 128 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 void* count_alternatives (int /*<<< orphan*/ ) ; 
 struct insn_def* defs ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int got_define_asm_attributes ; 
 void* insn_code_number ; 
 void* insn_index_number ; 
 struct insn_def* oballoc (int) ; 

__attribute__((used)) static void
gen_insn (rtx exp, int lineno)
{
  struct insn_def *id;

  id = oballoc (sizeof (struct insn_def));
  id->next = defs;
  defs = id;
  id->def = exp;
  id->lineno = lineno;

  switch (GET_CODE (exp))
    {
    case DEFINE_INSN:
      id->insn_code = insn_code_number;
      id->insn_index = insn_index_number;
      id->num_alternatives = count_alternatives (exp);
      if (id->num_alternatives == 0)
	id->num_alternatives = 1;
      id->vec_idx = 4;
      break;

    case DEFINE_PEEPHOLE:
      id->insn_code = insn_code_number;
      id->insn_index = insn_index_number;
      id->num_alternatives = count_alternatives (exp);
      if (id->num_alternatives == 0)
	id->num_alternatives = 1;
      id->vec_idx = 3;
      break;

    case DEFINE_ASM_ATTRIBUTES:
      id->insn_code = -1;
      id->insn_index = -1;
      id->num_alternatives = 1;
      id->vec_idx = 0;
      got_define_asm_attributes = 1;
      break;

    default:
      gcc_unreachable ();
    }
}