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
struct TYPE_2__ {int type; int /*<<< orphan*/  addr; } ;
struct v4l2_dbg_chip_ident {int /*<<< orphan*/  ident; int /*<<< orphan*/  revision; TYPE_1__ match; } ;
struct sd {size_t sensor; int /*<<< orphan*/  i2c_addr; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CHIP_MATCH_HOST 129 
#define  V4L2_CHIP_MATCH_I2C_ADDR 128 
 int /*<<< orphan*/  V4L2_IDENT_SN9C20X ; 
 int /*<<< orphan*/ * i2c_ident ; 

__attribute__((used)) static int sd_chip_ident(struct gspca_dev *gspca_dev,
			struct v4l2_dbg_chip_ident *chip)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (chip->match.type) {
	case V4L2_CHIP_MATCH_HOST:
		if (chip->match.addr != 0)
			return -EINVAL;
		chip->revision = 0;
		chip->ident = V4L2_IDENT_SN9C20X;
		return 0;
	case V4L2_CHIP_MATCH_I2C_ADDR:
		if (chip->match.addr != sd->i2c_addr)
			return -EINVAL;
		chip->revision = 0;
		chip->ident = i2c_ident[sd->sensor];
		return 0;
	}
	return -EINVAL;
}