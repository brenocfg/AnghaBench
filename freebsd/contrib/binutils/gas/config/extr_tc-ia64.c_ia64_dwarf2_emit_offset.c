#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_6__ {int /*<<< orphan*/ * X_add_symbol; scalar_t__ X_add_number; int /*<<< orphan*/  X_op_symbol; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_2__ expressionS ;
struct TYPE_5__ {int /*<<< orphan*/  sym; } ;
struct TYPE_7__ {TYPE_1__ u; } ;

/* Variables and functions */
 size_t FUNC_SEC_RELATIVE ; 
 int /*<<< orphan*/  O_pseudo_fixup ; 
 int /*<<< orphan*/  emit_expr (TYPE_2__*,unsigned int) ; 
 TYPE_3__* pseudo_func ; 

void
ia64_dwarf2_emit_offset (symbolS *symbol, unsigned int size)
{
  expressionS expr;

  expr.X_op = O_pseudo_fixup;
  expr.X_op_symbol = pseudo_func[FUNC_SEC_RELATIVE].u.sym;
  expr.X_add_number = 0;
  expr.X_add_symbol = symbol;
  emit_expr (&expr, size);
}