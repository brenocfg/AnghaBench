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
struct TYPE_3__ {int st_top; int st_nument; void** st_data; } ;
typedef  TYPE_1__ stk_t ;

/* Variables and functions */
 scalar_t__ STACK_SEEDSIZE ; 
 void** xrealloc (void**,int) ; 

void
stack_push(stk_t *sp, void *data)
{
	sp->st_top++;

	if (sp->st_top == sp->st_nument) {
		sp->st_nument += STACK_SEEDSIZE;
		sp->st_data = xrealloc(sp->st_data,
		    sizeof (void *) * sp->st_nument);
	}

	sp->st_data[sp->st_top] = data;
}