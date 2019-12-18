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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct file {int dummy; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct au0828_dev {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id * norm)
{
	struct au0828_fh *fh = priv;
	struct au0828_dev *dev = fh->dev;

	/* FIXME: when we support something other than NTSC, we are going to
	   have to make the au0828 bridge adjust the size of its capture
	   buffer, which is currently hardcoded at 720x480 */

	v4l2_device_call_all(&dev->v4l2_dev, 0, core, s_std, *norm);
	return 0;
}