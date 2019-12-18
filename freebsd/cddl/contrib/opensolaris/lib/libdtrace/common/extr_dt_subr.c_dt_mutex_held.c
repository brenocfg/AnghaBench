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
struct _lwp_mutex {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */

int
dt_mutex_held(pthread_mutex_t *lock)
{
#ifdef illumos
	extern int _mutex_held(struct _lwp_mutex *);
	return (_mutex_held((struct _lwp_mutex *)lock));
#else
	return (1);
#endif
}