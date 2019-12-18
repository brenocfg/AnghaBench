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
struct edd_info {int legacy_sectors_per_track; } ;
struct edd_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 struct edd_info* edd_dev_get_info (struct edd_device*) ; 
 int /*<<< orphan*/  left ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
edd_show_legacy_sectors_per_track(struct edd_device *edev, char *buf)
{
	struct edd_info *info;
	char *p = buf;
	if (!edev)
		return -EINVAL;
	info = edd_dev_get_info(edev);
	if (!info || !buf)
		return -EINVAL;

	p += snprintf(p, left, "%u\n", info->legacy_sectors_per_track);
	return (p - buf);
}