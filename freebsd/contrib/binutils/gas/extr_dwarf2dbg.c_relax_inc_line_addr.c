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
struct TYPE_3__ {scalar_t__ X_add_number; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF2_LINE_MIN_INSN_LENGTH ; 
 int /*<<< orphan*/  O_subtract ; 
 int /*<<< orphan*/  frag_var (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_expr_symbol (TYPE_1__*) ; 
 int /*<<< orphan*/  rs_dwarf2dbg ; 
 int size_inc_line_addr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
relax_inc_line_addr (int line_delta, symbolS *to_sym, symbolS *from_sym)
{
  expressionS expr;
  int max_chars;

  expr.X_op = O_subtract;
  expr.X_add_symbol = to_sym;
  expr.X_op_symbol = from_sym;
  expr.X_add_number = 0;

  /* The maximum size of the frag is the line delta with a maximum
     sized address delta.  */
  max_chars = size_inc_line_addr (line_delta, -DWARF2_LINE_MIN_INSN_LENGTH);

  frag_var (rs_dwarf2dbg, max_chars, max_chars, 1,
	    make_expr_symbol (&expr), line_delta, NULL);
}