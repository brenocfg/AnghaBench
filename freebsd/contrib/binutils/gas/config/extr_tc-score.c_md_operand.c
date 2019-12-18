#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  X_op; } ;
typedef  TYPE_1__ expressionS ;
struct TYPE_5__ {int /*<<< orphan*/ * error; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_illegal ; 
 int /*<<< orphan*/ * _ (char*) ; 
 scalar_t__ in_my_get_expression ; 
 TYPE_3__ inst ; 

void
md_operand (expressionS * expr)
{
  if (in_my_get_expression)
    {
      expr->X_op = O_illegal;
      if (inst.error == NULL)
        {
          inst.error = _("bad expression");
        }
    }
}