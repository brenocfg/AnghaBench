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
struct TYPE_2__ {int /*<<< orphan*/  hidden; } ;

/* Variables and functions */
 int current_class_depth ; 
 TYPE_1__* current_class_stack ; 

void
push_class_stack (void)
{
  if (current_class_depth)
    ++current_class_stack[current_class_depth - 1].hidden;
}