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
typedef  int ssize_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PAGE_SHARED ; 
 scalar_t__ likely (unsigned long) ; 
 int /*<<< orphan*/  pgprot_val (int /*<<< orphan*/ ) ; 
 int sq_remap (unsigned long,unsigned long,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sq_unmap (unsigned long) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*,unsigned long*) ; 

__attribute__((used)) static ssize_t mapping_store(const char *buf, size_t count)
{
	unsigned long base = 0, len = 0;

	sscanf(buf, "%lx %lx", &base, &len);
	if (!base)
		return -EIO;

	if (likely(len)) {
		int ret = sq_remap(base, len, "Userspace",
				   pgprot_val(PAGE_SHARED));
		if (ret < 0)
			return ret;
	} else
		sq_unmap(base);

	return count;
}