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
typedef  int /*<<< orphan*/  mtx_t ;

/* Variables and functions */
 int __pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int mtx_unlock(mtx_t *mtx)
{
	/* The only cases where pthread_mutex_unlock can return an
	 * error are undefined behavior for C11 mtx_unlock, so we can
	 * assume it does not return an error and simply tail call. */
	return __pthread_mutex_unlock(mtx);
}