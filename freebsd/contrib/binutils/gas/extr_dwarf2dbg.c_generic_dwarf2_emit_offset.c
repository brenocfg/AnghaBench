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
struct TYPE_3__ {scalar_t__ X_add_number; int /*<<< orphan*/ * X_add_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  O_symbol ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void
generic_dwarf2_emit_offset (symbolS *symbol, unsigned int size)
{
  expressionS expr;

  expr.X_op = O_symbol;
  expr.X_add_symbol = symbol;
  expr.X_add_number = 0;
  emit_expr (&expr, size);
}