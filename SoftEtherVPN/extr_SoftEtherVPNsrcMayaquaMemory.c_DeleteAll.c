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
struct TYPE_3__ {int num_reserved; int /*<<< orphan*/  p; scalar_t__ num_item; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int INIT_NUM_RESERVED ; 
 int /*<<< orphan*/  ReAlloc (int /*<<< orphan*/ ,int) ; 

void DeleteAll(LIST *o)
{
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	o->num_item = 0;
	o->num_reserved = INIT_NUM_RESERVED;
	o->p = ReAlloc(o->p, sizeof(void *) * INIT_NUM_RESERVED);
}