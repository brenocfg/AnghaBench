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
struct TYPE_3__ {scalar_t__ st_top; void** st_data; } ;
typedef  TYPE_1__ stk_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void *
stack_pop(stk_t *sp)
{
	assert(sp->st_top >= 0);

	return (sp->st_data[sp->st_top--]);
}