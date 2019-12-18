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
struct v4l2_dbg_chip_ident {scalar_t__ ident; int /*<<< orphan*/  match; scalar_t__ revision; } ;
struct file {int dummy; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct au0828_dev {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_IDENT_AU0828 ; 
 scalar_t__ V4L2_IDENT_NONE ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  g_chip_ident ; 
 scalar_t__ v4l2_chip_match_host (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dbg_chip_ident*) ; 

__attribute__((used)) static int vidioc_g_chip_ident(struct file *file, void *priv,
	       struct v4l2_dbg_chip_ident *chip)
{
	struct au0828_fh *fh = priv;
	struct au0828_dev *dev = fh->dev;
	chip->ident = V4L2_IDENT_NONE;
	chip->revision = 0;

	if (v4l2_chip_match_host(&chip->match)) {
		chip->ident = V4L2_IDENT_AU0828;
		return 0;
	}

	v4l2_device_call_all(&dev->v4l2_dev, 0, core, g_chip_ident, chip);
	if (chip->ident == V4L2_IDENT_NONE)
		return -EINVAL;

	return 0;
}