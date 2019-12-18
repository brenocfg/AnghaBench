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
struct sd {int bridge; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  BRIDGE_SPCA504 130 
#define  BRIDGE_SPCA504C 129 
#define  BRIDGE_SPCA536 128 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  setbrightness (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcolors (struct gspca_dev*) ; 
 int /*<<< orphan*/  setcontrast (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504B_PollingDataReady (struct gspca_dev*) ; 

__attribute__((used)) static void init_ctl_reg(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int pollreg = 1;

	setbrightness(gspca_dev);
	setcontrast(gspca_dev);
	setcolors(gspca_dev);

	switch (sd->bridge) {
	case BRIDGE_SPCA504:
	case BRIDGE_SPCA504C:
		pollreg = 0;
		/* fall thru */
	default:
/*	case BRIDGE_SPCA533: */
/*	case BRIDGE_SPCA504B: */
		reg_w_riv(gspca_dev, 0, 0x21ad, 0x00);	/* hue */
		reg_w_riv(gspca_dev, 0, 0x21ac, 0x01);	/* sat/hue */
		reg_w_riv(gspca_dev, 0, 0x21a3, 0x00);	/* gamma */
		break;
	case BRIDGE_SPCA536:
		reg_w_riv(gspca_dev, 0, 0x20f5, 0x40);
		reg_w_riv(gspca_dev, 0, 0x20f4, 0x01);
		reg_w_riv(gspca_dev, 0, 0x2089, 0x00);
		break;
	}
	if (pollreg)
		spca504B_PollingDataReady(gspca_dev);
}