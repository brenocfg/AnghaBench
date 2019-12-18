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
struct warm_cache_op {int ops; unsigned long addr; unsigned long size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARMC_CACHE_OP ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,struct warm_cache_op*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sys_cacheflush (void*,char*) ; 
 scalar_t__ warm_fd ; 

int warm_cache_op_range(int op, void *addr, unsigned long size)
{
	struct warm_cache_op wop;
	int ret;

	if (warm_fd < 0) {
		/* note that this won't work for warm_cache_op_all */
		sys_cacheflush(addr, (char *)addr + size);
		return -1;
	}

	wop.ops = op;
	wop.addr = (unsigned long)addr;
	wop.size = size;

	ret = ioctl(warm_fd, WARMC_CACHE_OP, &wop);
	if (ret != 0) {
		perror("WARMC_CACHE_OP failed");
		return -1;
	}

	return 0;
}