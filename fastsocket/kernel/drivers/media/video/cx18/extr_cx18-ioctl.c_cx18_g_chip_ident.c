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
struct v4l2_dbg_chip_ident {scalar_t__ revision; int /*<<< orphan*/  ident; TYPE_1__ match; } ;
struct file {int dummy; } ;
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_HW_418_AV ; 
 int EINVAL ; 
#define  V4L2_CHIP_MATCH_HOST 130 
#define  V4L2_CHIP_MATCH_I2C_ADDR 129 
#define  V4L2_CHIP_MATCH_I2C_DRIVER 128 
 int /*<<< orphan*/  V4L2_IDENT_CX23418 ; 
 int /*<<< orphan*/  V4L2_IDENT_NONE ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  cx18_call_all (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dbg_chip_ident*) ; 
 int /*<<< orphan*/  cx18_call_hw (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dbg_chip_ident*) ; 
 scalar_t__ cx18_read_reg (struct cx18*,int) ; 
 int /*<<< orphan*/  g_chip_ident ; 

__attribute__((used)) static int cx18_g_chip_ident(struct file *file, void *fh,
				struct v4l2_dbg_chip_ident *chip)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;
	int err = 0;

	chip->ident = V4L2_IDENT_NONE;
	chip->revision = 0;
	switch (chip->match.type) {
	case V4L2_CHIP_MATCH_HOST:
		switch (chip->match.addr) {
		case 0:
			chip->ident = V4L2_IDENT_CX23418;
			chip->revision = cx18_read_reg(cx, 0xC72028);
			break;
		case 1:
			/*
			 * The A/V decoder is always present, but in the rare
			 * case that the card doesn't have analog, we don't
			 * use it.  We find it w/o using the cx->sd_av pointer
			 */
			cx18_call_hw(cx, CX18_HW_418_AV,
				     core, g_chip_ident, chip);
			break;
		default:
			/*
			 * Could return ident = V4L2_IDENT_UNKNOWN if we had
			 * other host chips at higher addresses, but we don't
			 */
			err = -EINVAL; /* per V4L2 spec */
			break;
		}
		break;
	case V4L2_CHIP_MATCH_I2C_DRIVER:
		/* If needed, returns V4L2_IDENT_AMBIGUOUS without extra work */
		cx18_call_all(cx, core, g_chip_ident, chip);
		break;
	case V4L2_CHIP_MATCH_I2C_ADDR:
		/*
		 * We could return V4L2_IDENT_UNKNOWN, but we don't do the work
		 * to look if a chip is at the address with no driver.  That's a
		 * dangerous thing to do with EEPROMs anyway.
		 */
		cx18_call_all(cx, core, g_chip_ident, chip);
		break;
	default:
		err = -EINVAL;
		break;
	}
	return err;
}