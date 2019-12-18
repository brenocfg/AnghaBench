#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int words; } ;

/* Variables and functions */
 scalar_t__ FIRST_PARM_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SPARC_INCOMING_INT_ARG_FIRST ; 
 int SPARC_INT_ARG_MAX ; 
 int UNITS_PER_WORD ; 
 TYPE_1__ current_function_args_info ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static rtx
sparc_builtin_saveregs (void)
{
  int first_reg = current_function_args_info.words;
  rtx address;
  int regno;

  for (regno = first_reg; regno < SPARC_INT_ARG_MAX; regno++)
    emit_move_insn (gen_rtx_MEM (word_mode,
				 gen_rtx_PLUS (Pmode,
					       frame_pointer_rtx,
					       GEN_INT (FIRST_PARM_OFFSET (0)
							+ (UNITS_PER_WORD
							   * regno)))),
		    gen_rtx_REG (word_mode,
				 SPARC_INCOMING_INT_ARG_FIRST + regno));

  address = gen_rtx_PLUS (Pmode,
			  frame_pointer_rtx,
			  GEN_INT (FIRST_PARM_OFFSET (0)
				   + UNITS_PER_WORD * first_reg));

  return address;
}