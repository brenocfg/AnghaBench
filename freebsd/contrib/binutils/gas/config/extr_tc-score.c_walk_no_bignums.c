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
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_2__ {scalar_t__ X_op; int /*<<< orphan*/ * X_op_symbol; int /*<<< orphan*/ * X_add_symbol; } ;

/* Variables and functions */
 scalar_t__ O_big ; 
 TYPE_1__* symbol_get_value_expression (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
walk_no_bignums (symbolS * sp)
{
  if (symbol_get_value_expression (sp)->X_op == O_big)
    return 1;

  if (symbol_get_value_expression (sp)->X_add_symbol)
    return (walk_no_bignums (symbol_get_value_expression (sp)->X_add_symbol)
	    || (symbol_get_value_expression (sp)->X_op_symbol
		&& walk_no_bignums (symbol_get_value_expression (sp)->X_op_symbol)));  

  return 0;
}