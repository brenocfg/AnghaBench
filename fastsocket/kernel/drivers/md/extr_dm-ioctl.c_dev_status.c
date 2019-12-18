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
struct mapped_device {int dummy; } ;
struct dm_ioctl {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  __dev_status (struct mapped_device*,struct dm_ioctl*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 struct mapped_device* find_device (struct dm_ioctl*) ; 

__attribute__((used)) static int dev_status(struct dm_ioctl *param, size_t param_size)
{
	struct mapped_device *md;

	md = find_device(param);
	if (!md)
		return -ENXIO;

	__dev_status(md, param);
	dm_put(md);

	return 0;
}