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
struct warm_change_cb {unsigned long addr; unsigned long size; int cb; int is_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARMC_CHANGE_CB ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,struct warm_change_cb*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ warm_fd ; 

int warm_change_cb_range(int cb, int is_set, void *addr, unsigned long size)
{
	struct warm_change_cb ccb;
	int ret;

	if (warm_fd < 0)
		return -1;
	
	ccb.addr = (unsigned long)addr;
	ccb.size = size;
	ccb.cb = cb;
	ccb.is_set = is_set;

	ret = ioctl(warm_fd, WARMC_CHANGE_CB, &ccb);
	if (ret != 0) {
		perror("WARMC_CHANGE_CB failed");
		return -1;
	}

	return 0;
}