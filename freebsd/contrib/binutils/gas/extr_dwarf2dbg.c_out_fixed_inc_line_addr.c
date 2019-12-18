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
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_3__ {scalar_t__ X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; void* X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  DW_LNE_end_sequence ; 
 int /*<<< orphan*/  DW_LNS_advance_line ; 
 int /*<<< orphan*/  DW_LNS_copy ; 
 int /*<<< orphan*/  DW_LNS_extended_op ; 
 int /*<<< orphan*/  DW_LNS_fixed_advance_pc ; 
 int INT_MAX ; 
 void* O_subtract ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  out_byte (int) ; 
 int /*<<< orphan*/  out_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_sleb128 (int) ; 

__attribute__((used)) static void
out_fixed_inc_line_addr (int line_delta, symbolS *to_sym, symbolS *from_sym)
{
  expressionS expr;

  /* INT_MAX is a signal that this is actually a DW_LNE_end_sequence.  */
  if (line_delta == INT_MAX)
    {
      out_opcode (DW_LNS_fixed_advance_pc);
      expr.X_op = O_subtract;
      expr.X_add_symbol = to_sym;
      expr.X_op_symbol = from_sym;
      expr.X_add_number = 0;
      emit_expr (&expr, 2);

      out_opcode (DW_LNS_extended_op);
      out_byte (1);
      out_opcode (DW_LNE_end_sequence);
      return;
    }

  out_opcode (DW_LNS_advance_line);
  out_sleb128 (line_delta);

  out_opcode (DW_LNS_fixed_advance_pc);
  expr.X_op = O_subtract;
  expr.X_add_symbol = to_sym;
  expr.X_op_symbol = from_sym;
  expr.X_add_number = 0;
  emit_expr (&expr, 2);

  out_opcode (DW_LNS_copy);
}