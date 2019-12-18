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
struct v4l2_cropcap {int dummy; } ;
struct soc_camera_host {TYPE_2__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_1__ dev; } ;
struct file {struct soc_camera_device* private_data; } ;
struct TYPE_4__ {int (* cropcap ) (struct soc_camera_device*,struct v4l2_cropcap*) ;} ;

/* Variables and functions */
 int stub1 (struct soc_camera_device*,struct v4l2_cropcap*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int soc_camera_cropcap(struct file *file, void *fh,
			      struct v4l2_cropcap *a)
{
	struct soc_camera_device *icd = file->private_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);

	return ici->ops->cropcap(icd, a);
}