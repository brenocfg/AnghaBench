#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int st_top; struct TYPE_5__* st_data; int /*<<< orphan*/  (* st_free ) (TYPE_1__) ;} ;
typedef  TYPE_1__ stk_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__) ; 

void
stack_free(stk_t *sp)
{
	int i;

	if (sp->st_free) {
		for (i = 0; i <= sp->st_top; i++)
			sp->st_free(sp->st_data[i]);
	}
	free(sp->st_data);
	free(sp);
}