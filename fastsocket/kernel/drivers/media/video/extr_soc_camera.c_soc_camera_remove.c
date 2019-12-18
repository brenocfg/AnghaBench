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
struct video_device {int dummy; } ;
struct soc_camera_link {int /*<<< orphan*/  regulators; int /*<<< orphan*/  num_regulators; int /*<<< orphan*/  (* del_device ) (struct soc_camera_link*) ;scalar_t__ board_info; } ;
struct soc_camera_device {struct video_device* vdev; } ;
struct device_driver {int /*<<< orphan*/  owner; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct TYPE_2__ {struct device_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_camera_free_i2c (struct soc_camera_device*) ; 
 int /*<<< orphan*/  soc_camera_free_user_formats (struct soc_camera_device*) ; 
 int /*<<< orphan*/  stub1 (struct soc_camera_link*) ; 
 TYPE_1__* to_soc_camera_control (struct soc_camera_device*) ; 
 struct soc_camera_device* to_soc_camera_dev (struct device*) ; 
 struct soc_camera_link* to_soc_camera_link (struct soc_camera_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

__attribute__((used)) static int soc_camera_remove(struct device *dev)
{
	struct soc_camera_device *icd = to_soc_camera_dev(dev);
	struct soc_camera_link *icl = to_soc_camera_link(icd);
	struct video_device *vdev = icd->vdev;

	BUG_ON(!dev->parent);

	if (vdev) {
		video_unregister_device(vdev);
		icd->vdev = NULL;
	}

	if (icl->board_info) {
		soc_camera_free_i2c(icd);
	} else {
		struct device_driver *drv = to_soc_camera_control(icd) ?
			to_soc_camera_control(icd)->driver : NULL;
		if (drv) {
			icl->del_device(icl);
			module_put(drv->owner);
		}
	}
	soc_camera_free_user_formats(icd);

	regulator_bulk_free(icl->num_regulators, icl->regulators);

	return 0;
}