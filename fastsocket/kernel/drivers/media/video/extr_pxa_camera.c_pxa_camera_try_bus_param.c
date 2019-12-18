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
struct soc_camera_host {struct pxa_camera_dev* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_2__* ops; TYPE_1__ dev; } ;
struct pxa_camera_dev {int dummy; } ;
struct TYPE_4__ {unsigned long (* query_bus_param ) (struct soc_camera_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ soc_camera_bus_param_compatible (unsigned long,unsigned long) ; 
 unsigned long stub1 (struct soc_camera_device*) ; 
 int test_platform_param (struct pxa_camera_dev*,unsigned char,unsigned long*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa_camera_try_bus_param(struct soc_camera_device *icd,
				    unsigned char buswidth)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct pxa_camera_dev *pcdev = ici->priv;
	unsigned long bus_flags, camera_flags;
	int ret = test_platform_param(pcdev, buswidth, &bus_flags);

	if (ret < 0)
		return ret;

	camera_flags = icd->ops->query_bus_param(icd);

	return soc_camera_bus_param_compatible(camera_flags, bus_flags) ? 0 : -EINVAL;
}