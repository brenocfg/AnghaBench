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

/* Variables and functions */
 int /*<<< orphan*/  READONLY () ; 
 int /*<<< orphan*/  WRITEONLY () ; 
 int /*<<< orphan*/  arena_purge (size_t const) ; 
 int /*<<< orphan*/  ctl_mtx ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
arena_i_purge_ctl(const size_t *mib, size_t miblen, void *oldp, size_t *oldlenp,
    void *newp, size_t newlen)
{
	int ret;

	READONLY();
	WRITEONLY();
	malloc_mutex_lock(&ctl_mtx);
	arena_purge(mib[1]);
	malloc_mutex_unlock(&ctl_mtx);

	ret = 0;
label_return:
	return (ret);
}