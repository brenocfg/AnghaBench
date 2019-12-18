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
struct TYPE_3__ {int st_top; void** st_data; } ;
typedef  TYPE_1__ stk_t ;

/* Variables and functions */

void *
stack_peek(stk_t *sp)
{
	if (sp->st_top == -1)
		return (NULL);

	return (sp->st_data[sp->st_top]);
}