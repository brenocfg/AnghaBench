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
struct symbol {int dummy; } ;
struct TYPE_2__ {unsigned char reg; } ;
struct axs_value {void* kind; TYPE_1__ u; } ;
struct agent_expr {int /*<<< orphan*/  scope; } ;
typedef  unsigned char ULONGEST ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 unsigned char DW_OP_fbreg ; 
 unsigned char DW_OP_reg0 ; 
 unsigned char DW_OP_reg31 ; 
 unsigned char DW_OP_regx ; 
 int /*<<< orphan*/  SYMBOL_PRINT_NAME (struct symbol*) ; 
 int /*<<< orphan*/  TARGET_VIRTUAL_FRAME_POINTER (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aop_add ; 
 int /*<<< orphan*/  ax_const_l (struct agent_expr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax_reg (struct agent_expr*,int) ; 
 int /*<<< orphan*/  ax_simple (struct agent_expr*,int /*<<< orphan*/ ) ; 
 void* axs_lvalue_memory ; 
 void* axs_lvalue_register ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 unsigned char* read_sleb128 (unsigned char*,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_uleb128 (unsigned char*,unsigned char*,unsigned char*) ; 

__attribute__((used)) static void
dwarf2_tracepoint_var_ref (struct symbol * symbol, struct agent_expr * ax,
			   struct axs_value * value, unsigned char *data,
			   int size)
{
  if (size == 0)
    error ("Symbol \"%s\" has been optimized out.",
	   SYMBOL_PRINT_NAME (symbol));

  if (size == 1
      && data[0] >= DW_OP_reg0
      && data[0] <= DW_OP_reg31)
    {
      value->kind = axs_lvalue_register;
      value->u.reg = data[0] - DW_OP_reg0;
    }
  else if (data[0] == DW_OP_regx)
    {
      ULONGEST reg;
      read_uleb128 (data + 1, data + size, &reg);
      value->kind = axs_lvalue_register;
      value->u.reg = reg;
    }
  else if (data[0] == DW_OP_fbreg)
    {
      /* And this is worse than just minimal; we should honor the frame base
	 as above.  */
      int frame_reg;
      LONGEST frame_offset;
      unsigned char *buf_end;

      buf_end = read_sleb128 (data + 1, data + size, &frame_offset);
      if (buf_end != data + size)
	error ("Unexpected opcode after DW_OP_fbreg for symbol \"%s\".",
	       SYMBOL_PRINT_NAME (symbol));

      TARGET_VIRTUAL_FRAME_POINTER (ax->scope, &frame_reg, &frame_offset);
      ax_reg (ax, frame_reg);
      ax_const_l (ax, frame_offset);
      ax_simple (ax, aop_add);

      ax_const_l (ax, frame_offset);
      ax_simple (ax, aop_add);
      value->kind = axs_lvalue_memory;
    }
  else
    error ("Unsupported DWARF opcode in the location of \"%s\".",
	   SYMBOL_PRINT_NAME (symbol));
}