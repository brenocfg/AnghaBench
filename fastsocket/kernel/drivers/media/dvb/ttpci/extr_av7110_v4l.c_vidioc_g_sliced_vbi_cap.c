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
struct v4l2_sliced_vbi_cap {scalar_t__ type; void*** service_lines; void* service_set; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct file {int dummy; } ;
struct av7110 {int /*<<< orphan*/  arm_app; } ;

/* Variables and functions */
 int EINVAL ; 
 int FW_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ V4L2_BUF_TYPE_SLICED_VBI_OUTPUT ; 
 void* V4L2_SLICED_WSS_625 ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 

__attribute__((used)) static int vidioc_g_sliced_vbi_cap(struct file *file, void *fh,
					struct v4l2_sliced_vbi_cap *cap)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct av7110 *av7110 = (struct av7110 *)dev->ext_priv;

	dprintk(2, "VIDIOC_G_SLICED_VBI_CAP\n");
	if (cap->type != V4L2_BUF_TYPE_SLICED_VBI_OUTPUT)
		return -EINVAL;
	if (FW_VERSION(av7110->arm_app) >= 0x2623) {
		cap->service_set = V4L2_SLICED_WSS_625;
		cap->service_lines[0][23] = V4L2_SLICED_WSS_625;
	}
	return 0;
}