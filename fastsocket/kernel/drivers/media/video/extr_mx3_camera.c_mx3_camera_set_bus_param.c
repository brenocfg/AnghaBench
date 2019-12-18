#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct soc_camera_host {struct mx3_camera_dev* priv; } ;
struct soc_camera_format_xlate {TYPE_3__* host_fmt; } ;
struct TYPE_4__ {struct device* parent; } ;
struct soc_camera_device {TYPE_2__* ops; int /*<<< orphan*/  buswidth; TYPE_1__ dev; } ;
struct mx3_camera_dev {int platform_flags; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {int depth; } ;
struct TYPE_5__ {unsigned long (* query_bus_param ) (struct soc_camera_device*) ;int (* set_bus_param ) (struct soc_camera_device*,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_SENS_CONF ; 
 int CSI_SENS_CONF_DATA_FMT_BAYER ; 
 int CSI_SENS_CONF_DATA_FMT_SHIFT ; 
 int CSI_SENS_CONF_DATA_POL_SHIFT ; 
 int CSI_SENS_CONF_DATA_WIDTH_SHIFT ; 
 int CSI_SENS_CONF_HSYNC_POL_SHIFT ; 
 int CSI_SENS_CONF_PIX_CLK_POL_SHIFT ; 
 int CSI_SENS_CONF_VSYNC_POL_SHIFT ; 
 int EINVAL ; 
 int MX3_CAMERA_DP ; 
 int MX3_CAMERA_HSP ; 
 int MX3_CAMERA_PCP ; 
 int MX3_CAMERA_VSP ; 
 unsigned long SOCAM_DATAWIDTH_10 ; 
 unsigned long SOCAM_DATAWIDTH_15 ; 
 unsigned long SOCAM_DATAWIDTH_4 ; 
 unsigned long SOCAM_DATAWIDTH_8 ; 
 unsigned long SOCAM_DATAWIDTH_MASK ; 
 unsigned long SOCAM_DATA_ACTIVE_HIGH ; 
 unsigned long SOCAM_DATA_ACTIVE_LOW ; 
 unsigned long SOCAM_HSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_LOW ; 
 unsigned long SOCAM_PCLK_SAMPLE_FALLING ; 
 unsigned long SOCAM_PCLK_SAMPLE_RISING ; 
 unsigned long SOCAM_VSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_VSYNC_ACTIVE_LOW ; 
 int csi_reg_read (struct mx3_camera_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csi_reg_write (struct mx3_camera_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 unsigned long soc_camera_bus_param_compatible (unsigned long,unsigned long) ; 
 struct soc_camera_format_xlate* soc_camera_xlate_by_fourcc (struct soc_camera_device*,int /*<<< orphan*/ ) ; 
 unsigned long stub1 (struct soc_camera_device*) ; 
 int stub2 (struct soc_camera_device*,unsigned long) ; 
 int test_platform_param (struct mx3_camera_dev*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct soc_camera_host* to_soc_camera_host (struct device*) ; 

__attribute__((used)) static int mx3_camera_set_bus_param(struct soc_camera_device *icd, __u32 pixfmt)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->dev.parent);
	struct mx3_camera_dev *mx3_cam = ici->priv;
	unsigned long bus_flags, camera_flags, common_flags;
	u32 dw, sens_conf;
	int ret = test_platform_param(mx3_cam, icd->buswidth, &bus_flags);
	const struct soc_camera_format_xlate *xlate;
	struct device *dev = icd->dev.parent;

	xlate = soc_camera_xlate_by_fourcc(icd, pixfmt);
	if (!xlate) {
		dev_warn(dev, "Format %x not found\n", pixfmt);
		return -EINVAL;
	}

	dev_dbg(dev, "requested bus width %d bit: %d\n",
		icd->buswidth, ret);

	if (ret < 0)
		return ret;

	camera_flags = icd->ops->query_bus_param(icd);

	common_flags = soc_camera_bus_param_compatible(camera_flags, bus_flags);
	dev_dbg(dev, "Flags cam: 0x%lx host: 0x%lx common: 0x%lx\n",
		camera_flags, bus_flags, common_flags);
	if (!common_flags) {
		dev_dbg(dev, "no common flags");
		return -EINVAL;
	}

	/* Make choices, based on platform preferences */
	if ((common_flags & SOCAM_HSYNC_ACTIVE_HIGH) &&
	    (common_flags & SOCAM_HSYNC_ACTIVE_LOW)) {
		if (mx3_cam->platform_flags & MX3_CAMERA_HSP)
			common_flags &= ~SOCAM_HSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~SOCAM_HSYNC_ACTIVE_LOW;
	}

	if ((common_flags & SOCAM_VSYNC_ACTIVE_HIGH) &&
	    (common_flags & SOCAM_VSYNC_ACTIVE_LOW)) {
		if (mx3_cam->platform_flags & MX3_CAMERA_VSP)
			common_flags &= ~SOCAM_VSYNC_ACTIVE_HIGH;
		else
			common_flags &= ~SOCAM_VSYNC_ACTIVE_LOW;
	}

	if ((common_flags & SOCAM_DATA_ACTIVE_HIGH) &&
	    (common_flags & SOCAM_DATA_ACTIVE_LOW)) {
		if (mx3_cam->platform_flags & MX3_CAMERA_DP)
			common_flags &= ~SOCAM_DATA_ACTIVE_HIGH;
		else
			common_flags &= ~SOCAM_DATA_ACTIVE_LOW;
	}

	if ((common_flags & SOCAM_PCLK_SAMPLE_RISING) &&
	    (common_flags & SOCAM_PCLK_SAMPLE_FALLING)) {
		if (mx3_cam->platform_flags & MX3_CAMERA_PCP)
			common_flags &= ~SOCAM_PCLK_SAMPLE_RISING;
		else
			common_flags &= ~SOCAM_PCLK_SAMPLE_FALLING;
	}

	/* Make the camera work in widest common mode, we'll take care of
	 * the rest */
	if (common_flags & SOCAM_DATAWIDTH_15)
		common_flags = (common_flags & ~SOCAM_DATAWIDTH_MASK) |
			SOCAM_DATAWIDTH_15;
	else if (common_flags & SOCAM_DATAWIDTH_10)
		common_flags = (common_flags & ~SOCAM_DATAWIDTH_MASK) |
			SOCAM_DATAWIDTH_10;
	else if (common_flags & SOCAM_DATAWIDTH_8)
		common_flags = (common_flags & ~SOCAM_DATAWIDTH_MASK) |
			SOCAM_DATAWIDTH_8;
	else
		common_flags = (common_flags & ~SOCAM_DATAWIDTH_MASK) |
			SOCAM_DATAWIDTH_4;

	ret = icd->ops->set_bus_param(icd, common_flags);
	if (ret < 0) {
		dev_dbg(dev, "camera set_bus_param(%lx) returned %d\n",
			common_flags, ret);
		return ret;
	}

	/*
	 * So far only gated clock mode is supported. Add a line
	 *	(3 << CSI_SENS_CONF_SENS_PRTCL_SHIFT) |
	 * below and select the required mode when supporting other
	 * synchronisation protocols.
	 */
	sens_conf = csi_reg_read(mx3_cam, CSI_SENS_CONF) &
		~((1 << CSI_SENS_CONF_VSYNC_POL_SHIFT) |
		  (1 << CSI_SENS_CONF_HSYNC_POL_SHIFT) |
		  (1 << CSI_SENS_CONF_DATA_POL_SHIFT) |
		  (1 << CSI_SENS_CONF_PIX_CLK_POL_SHIFT) |
		  (3 << CSI_SENS_CONF_DATA_FMT_SHIFT) |
		  (3 << CSI_SENS_CONF_DATA_WIDTH_SHIFT));

	/* TODO: Support RGB and YUV formats */

	/* This has been set in mx3_camera_activate(), but we clear it above */
	sens_conf |= CSI_SENS_CONF_DATA_FMT_BAYER;

	if (common_flags & SOCAM_PCLK_SAMPLE_FALLING)
		sens_conf |= 1 << CSI_SENS_CONF_PIX_CLK_POL_SHIFT;
	if (common_flags & SOCAM_HSYNC_ACTIVE_LOW)
		sens_conf |= 1 << CSI_SENS_CONF_HSYNC_POL_SHIFT;
	if (common_flags & SOCAM_VSYNC_ACTIVE_LOW)
		sens_conf |= 1 << CSI_SENS_CONF_VSYNC_POL_SHIFT;
	if (common_flags & SOCAM_DATA_ACTIVE_LOW)
		sens_conf |= 1 << CSI_SENS_CONF_DATA_POL_SHIFT;

	/* Just do what we're asked to do */
	switch (xlate->host_fmt->depth) {
	case 4:
		dw = 0 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;
		break;
	case 8:
		dw = 1 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;
		break;
	case 10:
		dw = 2 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;
		break;
	default:
		/*
		 * Actually it can only be 15 now, default is just to silence
		 * compiler warnings
		 */
	case 15:
		dw = 3 << CSI_SENS_CONF_DATA_WIDTH_SHIFT;
	}

	csi_reg_write(mx3_cam, sens_conf | dw, CSI_SENS_CONF);

	dev_dbg(dev, "Set SENS_CONF to %x\n", sens_conf | dw);

	return 0;
}