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
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_3__ {int X_unsigned; int /*<<< orphan*/  X_add_number; int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  O_constant ; 
 int /*<<< orphan*/ * make_expr_symbol (TYPE_1__*) ; 

symbolS *
expr_build_uconstant (offsetT value)
{
  expressionS e;

  e.X_op = O_constant;
  e.X_add_number = value;
  e.X_unsigned = 1;
  return make_expr_symbol (&e);
}