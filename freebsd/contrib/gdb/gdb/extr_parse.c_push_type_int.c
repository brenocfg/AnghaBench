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
struct TYPE_2__ {int int_val; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_type_stack_depth () ; 
 TYPE_1__* type_stack ; 
 int /*<<< orphan*/  type_stack_depth ; 

void
push_type_int (int n)
{
  check_type_stack_depth ();
  type_stack[type_stack_depth++].int_val = n;
}