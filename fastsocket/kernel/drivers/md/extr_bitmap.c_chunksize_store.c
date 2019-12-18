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
struct TYPE_2__ {unsigned long chunksize; } ;
struct mddev {TYPE_1__ bitmap_info; scalar_t__ bitmap; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t
chunksize_store(struct mddev *mddev, const char *buf, size_t len)
{
	/* Can only be changed when no bitmap is active */
	int rv;
	unsigned long csize;
	if (mddev->bitmap)
		return -EBUSY;
	rv = kstrtoul(buf, 10, &csize);
	if (rv)
		return rv;
	if (csize < 512 ||
	    !is_power_of_2(csize))
		return -EINVAL;
	mddev->bitmap_info.chunksize = csize;
	return len;
}