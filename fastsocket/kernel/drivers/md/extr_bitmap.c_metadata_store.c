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
struct TYPE_2__ {int external; scalar_t__ offset; scalar_t__ file; } ;
struct mddev {TYPE_1__ bitmap_info; scalar_t__ bitmap; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t metadata_store(struct mddev *mddev, const char *buf, size_t len)
{
	if (mddev->bitmap ||
	    mddev->bitmap_info.file ||
	    mddev->bitmap_info.offset)
		return -EBUSY;
	if (strncmp(buf, "external", 8) == 0)
		mddev->bitmap_info.external = 1;
	else if (strncmp(buf, "internal", 8) == 0)
		mddev->bitmap_info.external = 0;
	else
		return -EINVAL;
	return len;
}