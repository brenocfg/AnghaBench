#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ offsetT ;
struct TYPE_4__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 scalar_t__ O_absent ; 
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expression_and_evaluate (TYPE_1__*) ; 

__attribute__((used)) static offsetT
get_absolute_expr (expressionS *exp)
{
  expression_and_evaluate (exp);
  if (exp->X_op != O_constant)
    {
      if (exp->X_op != O_absent)
	as_bad (_("bad or irreducible absolute expression"));
      exp->X_add_number = 0;
    }
  return exp->X_add_number;
}