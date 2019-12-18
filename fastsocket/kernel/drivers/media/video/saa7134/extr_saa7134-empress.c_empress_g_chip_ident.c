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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  name; } ;
struct v4l2_dbg_chip_ident {TYPE_1__ match; scalar_t__ revision; int /*<<< orphan*/  ident; } ;
struct saa7134_dev {int dummy; } ;
struct file {struct saa7134_dev* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_CHIP_MATCH_I2C_ADDR ; 
 scalar_t__ V4L2_CHIP_MATCH_I2C_DRIVER ; 
 int /*<<< orphan*/  V4L2_IDENT_NONE ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  g_chip_ident ; 
 int saa_call_empress (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dbg_chip_ident*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int empress_g_chip_ident(struct file *file, void *fh,
	       struct v4l2_dbg_chip_ident *chip)
{
	struct saa7134_dev *dev = file->private_data;

	chip->ident = V4L2_IDENT_NONE;
	chip->revision = 0;
	if (chip->match.type == V4L2_CHIP_MATCH_I2C_DRIVER &&
	    !strcmp(chip->match.name, "saa6752hs"))
		return saa_call_empress(dev, core, g_chip_ident, chip);
	if (chip->match.type == V4L2_CHIP_MATCH_I2C_ADDR)
		return saa_call_empress(dev, core, g_chip_ident, chip);
	return -EINVAL;
}