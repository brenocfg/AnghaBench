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
struct TYPE_3__ {unsigned int X_add_number; } ;
typedef  TYPE_1__ expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  expr_normal ; 
 int /*<<< orphan*/  operand (TYPE_1__*,int /*<<< orphan*/ ) ; 

unsigned int
get_single_number (void)
{
  expressionS exp;
  operand (&exp, expr_normal);
  return exp.X_add_number;
}