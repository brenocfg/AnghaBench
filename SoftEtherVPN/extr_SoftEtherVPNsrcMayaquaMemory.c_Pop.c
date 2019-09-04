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
struct TYPE_3__ {int num_item; int no_compact; int num_reserved; void** p; } ;
typedef  TYPE_1__ SK ;

/* Variables and functions */
 int INIT_NUM_RESERVED ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_POP_COUNT ; 
 void** ReAlloc (void**,int) ; 

void *Pop(SK *s)
{
	void *ret;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}
	if (s->num_item == 0)
	{
		return NULL;
	}
	ret = s->p[s->num_item - 1];
	s->num_item--;

	// Size reduction
	if (s->no_compact == false)
	{
		// Not to shrink when no_compact is true
		if ((s->num_item * 2) <= s->num_reserved)
		{
			if (s->num_reserved >= (INIT_NUM_RESERVED * 2))
			{
				s->num_reserved = s->num_reserved / 2;
				s->p = ReAlloc(s->p, sizeof(void *) * s->num_reserved);
			}
		}
	}

	// KS
	KS_INC(KS_POP_COUNT);

	return ret;
}