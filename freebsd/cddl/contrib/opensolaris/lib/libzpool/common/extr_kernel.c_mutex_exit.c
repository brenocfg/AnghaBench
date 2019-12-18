#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ initialized; int /*<<< orphan*/  m_lock; int /*<<< orphan*/ * m_owner; } ;
typedef  TYPE_1__ kmutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ curthread ; 
 scalar_t__ mutex_owner (TYPE_1__*) ; 
 scalar_t__ mutex_unlock (int /*<<< orphan*/ *) ; 

void
mutex_exit(kmutex_t *mp)
{
	ASSERT(mp->initialized == B_TRUE);
	ASSERT(mutex_owner(mp) == curthread);
	mp->m_owner = NULL;
	VERIFY(mutex_unlock(&mp->m_lock) == 0);
}