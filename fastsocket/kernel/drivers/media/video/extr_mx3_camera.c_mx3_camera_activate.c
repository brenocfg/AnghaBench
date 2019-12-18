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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {TYPE_1__ dev; } ;
struct mx3_camera_dev {int platform_flags; int /*<<< orphan*/  clk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_ACT_FRM_SIZE ; 
 int /*<<< orphan*/  CSI_OUT_FRM_CTRL ; 
 int /*<<< orphan*/  CSI_SENS_CONF ; 
 int CSI_SENS_CONF_DATA_FMT_BAYER ; 
 int CSI_SENS_CONF_DATA_POL_SHIFT ; 
 int CSI_SENS_CONF_DATA_WIDTH_SHIFT ; 
 int CSI_SENS_CONF_EXT_VSYNC_SHIFT ; 
 int CSI_SENS_CONF_HSYNC_POL_SHIFT ; 
 int CSI_SENS_CONF_PIX_CLK_POL_SHIFT ; 
 int CSI_SENS_CONF_SENS_CLKSRC_SHIFT ; 
 int CSI_SENS_CONF_SENS_PRTCL_SHIFT ; 
 int CSI_SENS_CONF_VSYNC_POL_SHIFT ; 
 int MX3_CAMERA_CLK_SRC ; 
 int MX3_CAMERA_DATAWIDTH_10 ; 
 int MX3_CAMERA_DATAWIDTH_15 ; 
 int MX3_CAMERA_DATAWIDTH_8 ; 
 int MX3_CAMERA_DP ; 
 int MX3_CAMERA_EXT_VSYNC ; 
 int MX3_CAMERA_HSP ; 
 int MX3_CAMERA_PCP ; 
 int MX3_CAMERA_VSP ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 long clk_round_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,long) ; 
 int csi_reg_read (struct mx3_camera_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csi_reg_write (struct mx3_camera_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,long) ; 

__attribute__((used)) static void mx3_camera_activate(struct mx3_camera_dev *mx3_cam,
				struct soc_camera_device *icd)
{
	u32 conf;
	long rate;

	/* Set default size: ipu_csi_set_window_size() */
	csi_reg_write(mx3_cam, (640 - 1) | ((480 - 1) << 16), CSI_ACT_FRM_SIZE);
	/* ...and position to 0:0: ipu_csi_set_window_pos() */
	conf = csi_reg_read(mx3_cam, CSI_OUT_FRM_CTRL) & 0xffff0000;
	csi_reg_write(mx3_cam, conf, CSI_OUT_FRM_CTRL);

	/* We use only gated clock synchronisation mode so far */
	conf = 0 << CSI_SENS_CONF_SENS_PRTCL_SHIFT;

	/* Set generic data, platform-biggest bus-width */
	conf |= CSI_SENS_CONF_DATA_FMT_BAYER;

	if (mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_15)
		conf |= 3 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;
	else if (mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_10)
		conf |= 2 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;
	else if (mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_8)
		conf |= 1 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;
	else/* if (mx3_cam->platform_flags & MX3_CAMERA_DATAWIDTH_4)*/
		conf |= 0 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;

	if (mx3_cam->platform_flags & MX3_CAMERA_CLK_SRC)
		conf |= 1 << CSI_SENS_CONF_SENS_CLKSRC_SHIFT;
	if (mx3_cam->platform_flags & MX3_CAMERA_EXT_VSYNC)
		conf |= 1 << CSI_SENS_CONF_EXT_VSYNC_SHIFT;
	if (mx3_cam->platform_flags & MX3_CAMERA_DP)
		conf |= 1 << CSI_SENS_CONF_DATA_POL_SHIFT;
	if (mx3_cam->platform_flags & MX3_CAMERA_PCP)
		conf |= 1 << CSI_SENS_CONF_PIX_CLK_POL_SHIFT;
	if (mx3_cam->platform_flags & MX3_CAMERA_HSP)
		conf |= 1 << CSI_SENS_CONF_HSYNC_POL_SHIFT;
	if (mx3_cam->platform_flags & MX3_CAMERA_VSP)
		conf |= 1 << CSI_SENS_CONF_VSYNC_POL_SHIFT;

	/* ipu_csi_init_interface() */
	csi_reg_write(mx3_cam, conf, CSI_SENS_CONF);

	clk_enable(mx3_cam->clk);
	rate = clk_round_rate(mx3_cam->clk, mx3_cam->mclk);
	dev_dbg(icd->dev.parent, "Set SENS_CONF to %x, rate %ld\n", conf, rate);
	if (rate)
		clk_set_rate(mx3_cam->clk, rate);
}