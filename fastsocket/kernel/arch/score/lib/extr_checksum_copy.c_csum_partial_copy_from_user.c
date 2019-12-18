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
 int EFAULT ; 
 int copy_from_user (char*,char const*,int) ; 
 unsigned int csum_partial (char*,int,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

unsigned int csum_partial_copy_from_user(const char *src, char *dst,
					int len, unsigned int sum,
					int *err_ptr)
{
	int missing;

	missing = copy_from_user(dst, src, len);
	if (missing) {
		memset(dst + len - missing, 0, missing);
		*err_ptr = -EFAULT;
	}

	return csum_partial(dst, len, sum);
}