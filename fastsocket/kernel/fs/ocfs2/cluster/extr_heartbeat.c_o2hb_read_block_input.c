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
struct o2hb_region {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int ffs (unsigned long) ; 
 int hweight16 (unsigned long) ; 
 unsigned long simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int o2hb_read_block_input(struct o2hb_region *reg,
				 const char *page,
				 size_t count,
				 unsigned long *ret_bytes,
				 unsigned int *ret_bits)
{
	unsigned long bytes;
	char *p = (char *)page;

	bytes = simple_strtoul(p, &p, 0);
	if (!p || (*p && (*p != '\n')))
		return -EINVAL;

	/* Heartbeat and fs min / max block sizes are the same. */
	if (bytes > 4096 || bytes < 512)
		return -ERANGE;
	if (hweight16(bytes) != 1)
		return -EINVAL;

	if (ret_bytes)
		*ret_bytes = bytes;
	if (ret_bits)
		*ret_bits = ffs(bytes) - 1;

	return 0;
}