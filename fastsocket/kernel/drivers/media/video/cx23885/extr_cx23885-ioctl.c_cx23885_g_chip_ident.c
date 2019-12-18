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
typedef  int u8 ;
struct TYPE_3__ {int type; int /*<<< orphan*/  addr; } ;
struct v4l2_dbg_chip_ident {int revision; void* ident; TYPE_1__ match; } ;
struct file {int dummy; } ;
struct cx23885_fh {struct cx23885_dev* dev; } ;
struct cx23885_dev {int hwrevision; int /*<<< orphan*/ * v4l_device; TYPE_2__* pci; } ;
struct TYPE_4__ {int device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX23885_HW_888_IR ; 
 int EINVAL ; 
 int /*<<< orphan*/  RDR_CFG2 ; 
#define  V4L2_CHIP_MATCH_HOST 130 
#define  V4L2_CHIP_MATCH_I2C_ADDR 129 
#define  V4L2_CHIP_MATCH_I2C_DRIVER 128 
 void* V4L2_IDENT_CX23417 ; 
 void* V4L2_IDENT_CX23885 ; 
 void* V4L2_IDENT_CX23887 ; 
 void* V4L2_IDENT_CX23888 ; 
 void* V4L2_IDENT_NONE ; 
 void* V4L2_IDENT_UNKNOWN ; 
 int /*<<< orphan*/  call_all (struct cx23885_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dbg_chip_ident*) ; 
 int /*<<< orphan*/  call_hw (struct cx23885_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_dbg_chip_ident*) ; 
 int /*<<< orphan*/  core ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_chip_ident ; 

int cx23885_g_chip_ident(struct file *file, void *fh,
			 struct v4l2_dbg_chip_ident *chip)
{
	struct cx23885_dev *dev = ((struct cx23885_fh *)fh)->dev;
	int err = 0;
	u8 rev;

	chip->ident = V4L2_IDENT_NONE;
	chip->revision = 0;
	switch (chip->match.type) {
	case V4L2_CHIP_MATCH_HOST:
		switch (chip->match.addr) {
		case 0:
			rev = cx_read(RDR_CFG2) & 0xff;
			switch (dev->pci->device) {
			case 0x8852:
				/* rev 0x04 could be '885 or '888. Pick '888. */
				if (rev == 0x04)
					chip->ident = V4L2_IDENT_CX23888;
				else
					chip->ident = V4L2_IDENT_CX23885;
				break;
			case 0x8880:
				if (rev == 0x0e || rev == 0x0f)
					chip->ident = V4L2_IDENT_CX23887;
				else
					chip->ident = V4L2_IDENT_CX23888;
				break;
			default:
				chip->ident = V4L2_IDENT_UNKNOWN;
				break;
			}
			chip->revision = (dev->pci->device << 16) | (rev << 8) |
					 (dev->hwrevision & 0xff);
			break;
		case 1:
			if (dev->v4l_device != NULL) {
				chip->ident = V4L2_IDENT_CX23417;
				chip->revision = 0;
			}
			break;
		case 2:
			/*
			 * The integrated IR controller on the CX23888 is
			 * host chip 2.  It may not be used/initialized or sd_ir
			 * may be pointing at the cx25840 subdevice for the
			 * IR controller on the CX23885.  Thus we find it
			 * without using the dev->sd_ir pointer.
			 */
			call_hw(dev, CX23885_HW_888_IR, core, g_chip_ident,
				chip);
			break;
		default:
			err = -EINVAL; /* per V4L2 spec */
			break;
		}
		break;
	case V4L2_CHIP_MATCH_I2C_DRIVER:
		/* If needed, returns V4L2_IDENT_AMBIGUOUS without extra work */
		call_all(dev, core, g_chip_ident, chip);
		break;
	case V4L2_CHIP_MATCH_I2C_ADDR:
		/*
		 * We could return V4L2_IDENT_UNKNOWN, but we don't do the work
		 * to look if a chip is at the address with no driver.  That's a
		 * dangerous thing to do with EEPROMs anyway.
		 */
		call_all(dev, core, g_chip_ident, chip);
		break;
	default:
		err = -EINVAL;
		break;
	}
	return err;
}