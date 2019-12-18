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
struct vio_driver {int (* probe ) (struct vio_dev*,struct vio_device_id const*) ;int /*<<< orphan*/  id_table; } ;
struct vio_device_id {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  cmo; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FW_FEATURE_CMO ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct vio_dev*,struct vio_device_id const*) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 
 struct vio_driver* to_vio_driver (int /*<<< orphan*/ ) ; 
 int vio_cmo_bus_probe (struct vio_dev*) ; 
 int /*<<< orphan*/  vio_cmo_bus_remove (struct vio_dev*) ; 
 struct vio_device_id* vio_match_device (int /*<<< orphan*/ ,struct vio_dev*) ; 

__attribute__((used)) static int vio_bus_probe(struct device *dev)
{
	struct vio_dev *viodev = to_vio_dev(dev);
	struct vio_driver *viodrv = to_vio_driver(dev->driver);
	const struct vio_device_id *id;
	int error = -ENODEV;

	if (!viodrv->probe)
		return error;

	id = vio_match_device(viodrv->id_table, viodev);
	if (id) {
		memset(&viodev->cmo, 0, sizeof(viodev->cmo));
		if (firmware_has_feature(FW_FEATURE_CMO)) {
			error = vio_cmo_bus_probe(viodev);
			if (error)
				return error;
		}
		error = viodrv->probe(viodev, id);
		if (error && firmware_has_feature(FW_FEATURE_CMO))
			vio_cmo_bus_remove(viodev);
	}

	return error;
}