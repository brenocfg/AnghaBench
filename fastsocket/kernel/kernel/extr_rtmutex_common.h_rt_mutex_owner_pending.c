#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rt_mutex {scalar_t__ owner; } ;

/* Variables and functions */
 unsigned long RT_MUTEX_OWNER_PENDING ; 

__attribute__((used)) static inline unsigned long rt_mutex_owner_pending(struct rt_mutex *lock)
{
	return (unsigned long)lock->owner & RT_MUTEX_OWNER_PENDING;
}