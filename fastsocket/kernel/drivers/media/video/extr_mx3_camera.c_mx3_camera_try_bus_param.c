#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_2__ dev; TYPE_1__* ops; } ;
struct mx3_camera_dev {int dummy; } ;
struct TYPE_3__ {unsigned long (* query_bus_param ) (struct soc_camera_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int const,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int soc_camera_bus_param_compatible (unsigned long,unsigned long) ; 
 unsigned long stub1 (struct soc_camera_device*) ; 
 int test_platform_param (struct mx3_camera_dev*,unsigned int const,unsigned long*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx3_camera_try_bus_param(struct soc_camera_device *icd,
				    const unsigned int depth)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx3_camera_dev *mx3_cam = ici->priv;
	unsigned long bus_flags, camera_flags;
	int ret = test_platform_param(mx3_cam, depth, &bus_flags);

	dev_dbg(icd->dev.parent, "request bus width %d bit: %d\n", depth, ret);

	if (ret < 0)
		return ret;

	camera_flags = icd->ops->query_bus_param(icd);

	ret = soc_camera_bus_param_compatible(camera_flags, bus_flags);
	if (ret < 0)
		dev_warn(icd->dev.parent,
			 "Flags incompatible: camera %lx, host %lx\n",
			 camera_flags, bus_flags);

	return ret;
}