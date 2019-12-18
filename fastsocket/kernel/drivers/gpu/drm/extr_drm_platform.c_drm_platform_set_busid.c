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
struct drm_master {int unique_len; int unique_size; char* unique; } ;
struct drm_device {TYPE_1__* platformdev; int /*<<< orphan*/ * devname; } ;
struct TYPE_2__ {char* name; int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int drm_platform_set_busid(struct drm_device *dev, struct drm_master *master)
{
	int len, ret, id;

	master->unique_len = 13 + strlen(dev->platformdev->name);
	master->unique_size = master->unique_len;
	master->unique = kmalloc(master->unique_len + 1, GFP_KERNEL);

	if (master->unique == NULL)
		return -ENOMEM;

	id = dev->platformdev->id;

	/* if only a single instance of the platform device, id will be
	 * set to -1.. use 0 instead to avoid a funny looking bus-id:
	 */
	if (id == -1)
		id = 0;

	len = snprintf(master->unique, master->unique_len,
			"platform:%s:%02d", dev->platformdev->name, id);

	if (len > master->unique_len) {
		DRM_ERROR("Unique buffer overflowed\n");
		ret = -EINVAL;
		goto err;
	}

	dev->devname =
		kmalloc(strlen(dev->platformdev->name) +
			master->unique_len + 2, GFP_KERNEL);

	if (dev->devname == NULL) {
		ret = -ENOMEM;
		goto err;
	}

	sprintf(dev->devname, "%s@%s", dev->platformdev->name,
		master->unique);
	return 0;
err:
	return ret;
}