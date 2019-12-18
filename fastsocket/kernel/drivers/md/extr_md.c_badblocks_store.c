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
struct badblocks {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOSPC ; 
 int /*<<< orphan*/  md_clear_badblocks (struct badblocks*,unsigned long long,int) ; 
 scalar_t__ md_set_badblocks (struct badblocks*,unsigned long long,int,int) ; 
 int sscanf (char const*,char*,unsigned long long*,int*,char*) ; 

__attribute__((used)) static ssize_t
badblocks_store(struct badblocks *bb, const char *page, size_t len, int unack)
{
	unsigned long long sector;
	int length;
	char newline;
#ifdef DO_DEBUG
	/* Allow clearing via sysfs *only* for testing/debugging.
	 * Normally only a successful write may clear a badblock
	 */
	int clear = 0;
	if (page[0] == '-') {
		clear = 1;
		page++;
	}
#endif /* DO_DEBUG */

	switch (sscanf(page, "%llu %d%c", &sector, &length, &newline)) {
	case 3:
		if (newline != '\n')
			return -EINVAL;
	case 2:
		if (length <= 0)
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

#ifdef DO_DEBUG
	if (clear) {
		md_clear_badblocks(bb, sector, length);
		return len;
	}
#endif /* DO_DEBUG */
	if (md_set_badblocks(bb, sector, length, !unack))
		return len;
	else
		return -ENOSPC;
}