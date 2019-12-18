#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_control {scalar_t__ id; int value; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {TYPE_2__* ext_vv_data; scalar_t__ ext_priv; } ;
struct hexium {int cur_bw; scalar_t__ cur_std; } ;
struct file {int dummy; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {TYPE_1__* core_ops; } ;
struct TYPE_4__ {int (* vidioc_s_ctrl ) (struct file*,void*,struct v4l2_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int EINVAL ; 
 int HEXIUM_CONTROLS ; 
 scalar_t__ V4L2_CID_PRIVATE_BASE ; 
 scalar_t__ V4L2_STD_NTSC ; 
 scalar_t__ V4L2_STD_PAL ; 
 scalar_t__ V4L2_STD_SECAM ; 
 TYPE_3__* hexium_controls ; 
 int /*<<< orphan*/  hexium_ntsc ; 
 int /*<<< orphan*/  hexium_ntsc_bw ; 
 int /*<<< orphan*/  hexium_pal ; 
 int /*<<< orphan*/  hexium_pal_bw ; 
 int /*<<< orphan*/  hexium_secam ; 
 int /*<<< orphan*/  hexium_set_standard (struct hexium*,int /*<<< orphan*/ ) ; 
 int stub1 (struct file*,void*,struct v4l2_control*) ; 

__attribute__((used)) static int vidioc_s_ctrl(struct file *file, void *fh, struct v4l2_control *vc)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct hexium *hexium = (struct hexium *) dev->ext_priv;
	int i = 0;

	for (i = HEXIUM_CONTROLS - 1; i >= 0; i--) {
		if (hexium_controls[i].id == vc->id)
			break;
	}

	if (i < 0)
		return dev->ext_vv_data->core_ops->vidioc_s_ctrl(file, fh, vc);

	if (vc->id == V4L2_CID_PRIVATE_BASE)
		hexium->cur_bw = vc->value;

	DEB_D(("VIDIOC_S_CTRL BW:%d.\n", hexium->cur_bw));

	if (0 == hexium->cur_bw && V4L2_STD_PAL == hexium->cur_std) {
		hexium_set_standard(hexium, hexium_pal);
		return 0;
	}
	if (0 == hexium->cur_bw && V4L2_STD_NTSC == hexium->cur_std) {
		hexium_set_standard(hexium, hexium_ntsc);
		return 0;
	}
	if (0 == hexium->cur_bw && V4L2_STD_SECAM == hexium->cur_std) {
		hexium_set_standard(hexium, hexium_secam);
		return 0;
	}
	if (1 == hexium->cur_bw && V4L2_STD_PAL == hexium->cur_std) {
		hexium_set_standard(hexium, hexium_pal_bw);
		return 0;
	}
	if (1 == hexium->cur_bw && V4L2_STD_NTSC == hexium->cur_std) {
		hexium_set_standard(hexium, hexium_ntsc_bw);
		return 0;
	}
	if (1 == hexium->cur_bw && V4L2_STD_SECAM == hexium->cur_std)
		/* fixme: is there no bw secam mode? */
		return -EINVAL;

	return -EINVAL;
}