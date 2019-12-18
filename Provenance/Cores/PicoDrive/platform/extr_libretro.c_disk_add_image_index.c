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
typedef  int /*<<< orphan*/  disks ;

/* Variables and functions */
 int disk_count ; 

__attribute__((used)) static bool disk_add_image_index(void)
{
	if (disk_count >= sizeof(disks) / sizeof(disks[0]))
		return false;

	disk_count++;
	return true;
}