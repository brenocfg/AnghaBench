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
struct function {TYPE_1__* emit; } ;
struct emit_status {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int regno_pointer_align_length; int /*<<< orphan*/  regno_pointer_align; } ;
typedef  int REG_POINTER ;
typedef  int /*<<< orphan*/  REGNO_POINTER_ALIGN ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_WORD ; 
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  INIT_EXPANDERS ; 
 void* LAST_VIRTUAL_REGISTER ; 
 int /*<<< orphan*/  STACK_BOUNDARY ; 
 int /*<<< orphan*/  UNKNOWN_LOCATION ; 
 struct function* cfun ; 
 int cur_insn_uid ; 
 int /*<<< orphan*/ * first_insn ; 
 int /*<<< orphan*/  first_label_num ; 
 void* ggc_alloc (int) ; 
 int /*<<< orphan*/  ggc_alloc_cleared (int) ; 
 int /*<<< orphan*/  init_virtual_regs (TYPE_1__*) ; 
 int /*<<< orphan*/  label_num ; 
 int /*<<< orphan*/ * last_insn ; 
 int /*<<< orphan*/  last_location ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 void* reg_rtx_no ; 
 void* regno_reg_rtx ; 
 int /*<<< orphan*/ * seq_stack ; 
 int /*<<< orphan*/  static_regno_reg_rtx ; 

void
init_emit (void)
{
  struct function *f = cfun;

  f->emit = ggc_alloc (sizeof (struct emit_status));
  first_insn = NULL;
  last_insn = NULL;
  cur_insn_uid = 1;
  reg_rtx_no = LAST_VIRTUAL_REGISTER + 1;
  last_location = UNKNOWN_LOCATION;
  first_label_num = label_num;
  seq_stack = NULL;

  /* Init the tables that describe all the pseudo regs.  */

  f->emit->regno_pointer_align_length = LAST_VIRTUAL_REGISTER + 101;

  f->emit->regno_pointer_align
    = ggc_alloc_cleared (f->emit->regno_pointer_align_length
			 * sizeof (unsigned char));

  regno_reg_rtx
    = ggc_alloc (f->emit->regno_pointer_align_length * sizeof (rtx));

  /* Put copies of all the hard registers into regno_reg_rtx.  */
  memcpy (regno_reg_rtx,
	  static_regno_reg_rtx,
	  FIRST_PSEUDO_REGISTER * sizeof (rtx));

  /* Put copies of all the virtual register rtx into regno_reg_rtx.  */
  init_virtual_regs (f->emit);

  /* Indicate that the virtual registers and stack locations are
     all pointers.  */
  REG_POINTER (stack_pointer_rtx) = 1;
  REG_POINTER (frame_pointer_rtx) = 1;
  REG_POINTER (hard_frame_pointer_rtx) = 1;
  REG_POINTER (arg_pointer_rtx) = 1;

  REG_POINTER (virtual_incoming_args_rtx) = 1;
  REG_POINTER (virtual_stack_vars_rtx) = 1;
  REG_POINTER (virtual_stack_dynamic_rtx) = 1;
  REG_POINTER (virtual_outgoing_args_rtx) = 1;
  REG_POINTER (virtual_cfa_rtx) = 1;

#ifdef STACK_BOUNDARY
  REGNO_POINTER_ALIGN (STACK_POINTER_REGNUM) = STACK_BOUNDARY;
  REGNO_POINTER_ALIGN (FRAME_POINTER_REGNUM) = STACK_BOUNDARY;
  REGNO_POINTER_ALIGN (HARD_FRAME_POINTER_REGNUM) = STACK_BOUNDARY;
  REGNO_POINTER_ALIGN (ARG_POINTER_REGNUM) = STACK_BOUNDARY;

  REGNO_POINTER_ALIGN (VIRTUAL_INCOMING_ARGS_REGNUM) = STACK_BOUNDARY;
  REGNO_POINTER_ALIGN (VIRTUAL_STACK_VARS_REGNUM) = STACK_BOUNDARY;
  REGNO_POINTER_ALIGN (VIRTUAL_STACK_DYNAMIC_REGNUM) = STACK_BOUNDARY;
  REGNO_POINTER_ALIGN (VIRTUAL_OUTGOING_ARGS_REGNUM) = STACK_BOUNDARY;
  REGNO_POINTER_ALIGN (VIRTUAL_CFA_REGNUM) = BITS_PER_WORD;
#endif

#ifdef INIT_EXPANDERS
  INIT_EXPANDERS;
#endif
}