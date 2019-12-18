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
typedef  int u32 ;
struct v4l2_control {int id; int value; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_1__ dev; } ;
struct sh_mobile_ceu_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLFCR ; 
 int ENOIOCTLCMD ; 
#define  V4L2_CID_SHARPNESS 128 
 int ceu_read (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_ceu_get_ctrl(struct soc_camera_device *icd,
				  struct v4l2_control *ctrl)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	u32 val;

	switch (ctrl->id) {
	case V4L2_CID_SHARPNESS:
		val = ceu_read(pcdev, CLFCR);
		ctrl->value = val ^ 1;
		return 0;
	}
	return -ENOIOCTLCMD;
}