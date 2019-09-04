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
typedef  size_t UINT ;
struct TYPE_3__ {size_t num_item; size_t num_reserved; void** p; } ;
typedef  TYPE_1__ SK ;

/* Variables and functions */
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_PUSH_COUNT ; 
 void** ReAlloc (void**,int) ; 

void Push(SK *s, void *p)
{
	UINT i;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return;
	}

	i = s->num_item;
	s->num_item++;

	// Size expansion
	if (s->num_item > s->num_reserved)
	{
		s->num_reserved = s->num_reserved * 2;
		s->p = ReAlloc(s->p, sizeof(void *) * s->num_reserved);
	}
	s->p[i] = p;

	// KS
	KS_INC(KS_PUSH_COUNT);
}