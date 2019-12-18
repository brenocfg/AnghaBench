#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int jfs_flag; unsigned long ext2_flag; } ;

/* Variables and functions */
 TYPE_1__* jfs_map ; 

__attribute__((used)) static long jfs_map_ext2(unsigned long flags, int from)
{
	int index=0;
	long mapped=0;

	while (jfs_map[index].jfs_flag) {
		if (from) {
			if (jfs_map[index].ext2_flag & flags)
				mapped |= jfs_map[index].jfs_flag;
		} else {
			if (jfs_map[index].jfs_flag & flags)
				mapped |= jfs_map[index].ext2_flag;
		}
		index++;
	}
	return mapped;
}