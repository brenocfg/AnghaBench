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
struct mddev {int sync_speed_max; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int simple_strtoul (char const*,char**,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t
sync_max_store(struct mddev *mddev, const char *buf, size_t len)
{
	int max;
	char *e;
	if (strncmp(buf, "system", 6)==0) {
		mddev->sync_speed_max = 0;
		return len;
	}
	max = simple_strtoul(buf, &e, 10);
	if (buf == e || (*e && *e != '\n') || max <= 0)
		return -EINVAL;
	mddev->sync_speed_max = max;
	return len;
}