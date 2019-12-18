#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int mode; int clock_curr; int clock_min; int clock_max; int /*<<< orphan*/  nobt_vs_inv; int /*<<< orphan*/  nobt_hs_inv; int /*<<< orphan*/  latch_clk_inv; int /*<<< orphan*/  swap; int /*<<< orphan*/  bt_sync_correct; int /*<<< orphan*/  frame_start_on_rising_vs; } ;
struct TYPE_6__ {TYPE_1__ bt656; } ;
struct v4l2_ifparm {int if_type; TYPE_2__ u; } ;
struct TYPE_7__ {int xclk; } ;
struct TYPE_8__ {TYPE_3__ bt656; } ;
struct omap24xxcam_device {int if_type; int /*<<< orphan*/  dev; TYPE_4__ if_u; int /*<<< orphan*/  cc_ctrl; int /*<<< orphan*/  sdev; } ;

/* Variables and functions */
 int CAM_MCLK ; 
 int /*<<< orphan*/  CC_CTRL_BT_CORRECT ; 
 int /*<<< orphan*/  CC_CTRL_CC_EN ; 
 int /*<<< orphan*/  CC_CTRL_NOBT_HS_POL ; 
 int /*<<< orphan*/  CC_CTRL_NOBT_SYNCHRO ; 
 int /*<<< orphan*/  CC_CTRL_NOBT_VS_POL ; 
 int /*<<< orphan*/  CC_CTRL_PAR_CLK_POL ; 
 int /*<<< orphan*/  CC_CTRL_PAR_MODE_BT10 ; 
 int /*<<< orphan*/  CC_CTRL_PAR_MODE_BT8 ; 
 int /*<<< orphan*/  CC_CTRL_PAR_MODE_NOBT10 ; 
 int /*<<< orphan*/  CC_CTRL_PAR_MODE_NOBT12 ; 
 int /*<<< orphan*/  CC_CTRL_PAR_MODE_NOBT8 ; 
 int /*<<< orphan*/  CC_CTRL_PAR_ORDERCAM ; 
 int EINVAL ; 
#define  V4L2_IF_TYPE_BT656 133 
#define  V4L2_IF_TYPE_BT656_MODE_BT_10BIT 132 
#define  V4L2_IF_TYPE_BT656_MODE_BT_8BIT 131 
#define  V4L2_IF_TYPE_BT656_MODE_NOBT_10BIT 130 
#define  V4L2_IF_TYPE_BT656_MODE_NOBT_12BIT 129 
#define  V4L2_IF_TYPE_BT656_MODE_NOBT_8BIT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  omap24xxcam_core_xclk_set (struct omap24xxcam_device*,int) ; 
 int vidioc_int_g_ifparm (int /*<<< orphan*/ ,struct v4l2_ifparm*) ; 

__attribute__((used)) static int omap24xxcam_sensor_if_enable(struct omap24xxcam_device *cam)
{
	int rval;
	struct v4l2_ifparm p;

	rval = vidioc_int_g_ifparm(cam->sdev, &p);
	if (rval) {
		dev_err(cam->dev, "vidioc_int_g_ifparm failed with %d\n", rval);
		return rval;
	}

	cam->if_type = p.if_type;

	cam->cc_ctrl = CC_CTRL_CC_EN;

	switch (p.if_type) {
	case V4L2_IF_TYPE_BT656:
		if (p.u.bt656.frame_start_on_rising_vs)
			cam->cc_ctrl |= CC_CTRL_NOBT_SYNCHRO;
		if (p.u.bt656.bt_sync_correct)
			cam->cc_ctrl |= CC_CTRL_BT_CORRECT;
		if (p.u.bt656.swap)
			cam->cc_ctrl |= CC_CTRL_PAR_ORDERCAM;
		if (p.u.bt656.latch_clk_inv)
			cam->cc_ctrl |= CC_CTRL_PAR_CLK_POL;
		if (p.u.bt656.nobt_hs_inv)
			cam->cc_ctrl |= CC_CTRL_NOBT_HS_POL;
		if (p.u.bt656.nobt_vs_inv)
			cam->cc_ctrl |= CC_CTRL_NOBT_VS_POL;

		switch (p.u.bt656.mode) {
		case V4L2_IF_TYPE_BT656_MODE_NOBT_8BIT:
			cam->cc_ctrl |= CC_CTRL_PAR_MODE_NOBT8;
			break;
		case V4L2_IF_TYPE_BT656_MODE_NOBT_10BIT:
			cam->cc_ctrl |= CC_CTRL_PAR_MODE_NOBT10;
			break;
		case V4L2_IF_TYPE_BT656_MODE_NOBT_12BIT:
			cam->cc_ctrl |= CC_CTRL_PAR_MODE_NOBT12;
			break;
		case V4L2_IF_TYPE_BT656_MODE_BT_8BIT:
			cam->cc_ctrl |= CC_CTRL_PAR_MODE_BT8;
			break;
		case V4L2_IF_TYPE_BT656_MODE_BT_10BIT:
			cam->cc_ctrl |= CC_CTRL_PAR_MODE_BT10;
			break;
		default:
			dev_err(cam->dev,
				"bt656 interface mode %d not supported\n",
				p.u.bt656.mode);
			return -EINVAL;
		}
		/*
		 * The clock rate that the sensor wants has changed.
		 * We have to adjust the xclk from OMAP 2 side to
		 * match the sensor's wish as closely as possible.
		 */
		if (p.u.bt656.clock_curr != cam->if_u.bt656.xclk) {
			u32 xclk = p.u.bt656.clock_curr;
			u32 divisor;

			if (xclk == 0)
				return -EINVAL;

			if (xclk > CAM_MCLK)
				xclk = CAM_MCLK;

			divisor = CAM_MCLK / xclk;
			if (divisor * xclk < CAM_MCLK)
				divisor++;
			if (CAM_MCLK / divisor < p.u.bt656.clock_min
			    && divisor > 1)
				divisor--;
			if (divisor > 30)
				divisor = 30;

			xclk = CAM_MCLK / divisor;

			if (xclk < p.u.bt656.clock_min
			    || xclk > p.u.bt656.clock_max)
				return -EINVAL;

			cam->if_u.bt656.xclk = xclk;
		}
		omap24xxcam_core_xclk_set(cam, cam->if_u.bt656.xclk);
		break;
	default:
		/* FIXME: how about other interfaces? */
		dev_err(cam->dev, "interface type %d not supported\n",
			p.if_type);
		return -EINVAL;
	}

	return 0;
}