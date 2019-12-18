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
struct TYPE_3__ {scalar_t__ initialized; void* m_owner; int /*<<< orphan*/  m_lock; } ;
typedef  TYPE_1__ kmutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 void* curthread ; 
 scalar_t__ mutex_trylock (int /*<<< orphan*/ *) ; 

int
mutex_tryenter(kmutex_t *mp)
{
	ASSERT(mp->initialized == B_TRUE);
	ASSERT(mp->m_owner != (void *)-1UL);
	if (0 == mutex_trylock(&mp->m_lock)) {
		ASSERT(mp->m_owner == NULL);
		mp->m_owner = curthread;
		return (1);
	} else {
		return (0);
	}
}