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
struct o2hb_region {char* hr_dev_name; scalar_t__ hr_bdev; } ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 unsigned int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t o2hb_region_dev_read(struct o2hb_region *reg,
				    char *page)
{
	unsigned int ret = 0;

	if (reg->hr_bdev)
		ret = sprintf(page, "%s\n", reg->hr_dev_name);

	return ret;
}