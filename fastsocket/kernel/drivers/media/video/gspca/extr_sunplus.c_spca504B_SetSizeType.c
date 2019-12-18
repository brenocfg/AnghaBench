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
struct sd {int bridge; int /*<<< orphan*/  subtype; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {size_t curr_mode; TYPE_2__ cam; } ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AiptekMiniPenCam13 ; 
#define  BRIDGE_SPCA504 130 
#define  BRIDGE_SPCA504C 129 
#define  BRIDGE_SPCA533 128 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_w_1 (struct gspca_dev*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  spca504A_acknowledged_command (struct gspca_dev*,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spca504B_PollingDataReady (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504B_WaitCmdStatus (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504_acknowledged_command (struct gspca_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spca50x_GetFirmware (struct gspca_dev*) ; 

__attribute__((used)) static void spca504B_SetSizeType(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 Size;

	Size = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	switch (sd->bridge) {
	case BRIDGE_SPCA533:
		reg_w_riv(gspca_dev, 0x31, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PollingDataReady(gspca_dev);
		spca50x_GetFirmware(gspca_dev);
		reg_w_1(gspca_dev, 0x24, 0, 8, 2);		/* type */
		reg_r(gspca_dev, 0x24, 8, 1);

		reg_w_1(gspca_dev, 0x25, 0, 4, Size);
		reg_r(gspca_dev, 0x25, 4, 1);			/* size */
		spca504B_PollingDataReady(gspca_dev);

		/* Init the cam width height with some values get on init ? */
		reg_w_riv(gspca_dev, 0x31, 0x0004, 0x00);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PollingDataReady(gspca_dev);
		break;
	default:
/* case BRIDGE_SPCA504B: */
/* case BRIDGE_SPCA536: */
		reg_w_1(gspca_dev, 0x25, 0, 4, Size);
		reg_r(gspca_dev, 0x25, 4, 1);			/* size */
		reg_w_1(gspca_dev, 0x27, 0, 0, 6);
		reg_r(gspca_dev, 0x27, 0, 1);			/* type */
		spca504B_PollingDataReady(gspca_dev);
		break;
	case BRIDGE_SPCA504:
		Size += 3;
		if (sd->subtype == AiptekMiniPenCam13) {
			/* spca504a aiptek */
			spca504A_acknowledged_command(gspca_dev,
						0x08, Size, 0,
						0x80 | (Size & 0x0f), 1);
			spca504A_acknowledged_command(gspca_dev,
							1, 3, 0, 0x9f, 0);
		} else {
			spca504_acknowledged_command(gspca_dev, 0x08, Size, 0);
		}
		break;
	case BRIDGE_SPCA504C:
		/* capture mode */
		reg_w_riv(gspca_dev, 0xa0, (0x0500 | (Size & 0x0f)), 0x00);
		reg_w_riv(gspca_dev, 0x20, 0x01, 0x0500 | (Size & 0x0f));
		break;
	}
}