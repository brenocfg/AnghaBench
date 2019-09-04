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
 int ENOENT ; 
 int /*<<< orphan*/  READONLY () ; 
 int /*<<< orphan*/  WRITEONLY () ; 
 int /*<<< orphan*/  config_tcache ; 
 int /*<<< orphan*/  tcache_flush () ; 

__attribute__((used)) static int
thread_tcache_flush_ctl(const size_t *mib, size_t miblen, void *oldp,
    size_t *oldlenp, void *newp, size_t newlen)
{
	int ret;

	if (!config_tcache)
		return (ENOENT);

	READONLY();
	WRITEONLY();

	tcache_flush();

	ret = 0;
label_return:
	return (ret);
}