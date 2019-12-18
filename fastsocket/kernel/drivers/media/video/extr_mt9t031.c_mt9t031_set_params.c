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
typedef  int u32 ;
typedef  int u16 ;
struct v4l2_rect {int left; int top; int width; int height; } ;
struct v4l2_queryctrl {unsigned int maximum; unsigned int minimum; } ;
struct mt9t031 {int yskip; int xskip; int y_skip_top; unsigned int exposure; struct v4l2_rect rect; scalar_t__ autoexposure; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T031_COLUMN_ADDRESS_MODE ; 
 int /*<<< orphan*/  MT9T031_COLUMN_SKIP ; 
 int /*<<< orphan*/  MT9T031_COLUMN_START ; 
 size_t MT9T031_CTRL_EXPOSURE ; 
 int MT9T031_HORIZONTAL_BLANK ; 
 int /*<<< orphan*/  MT9T031_HORIZONTAL_BLANKING ; 
 int MT9T031_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9T031_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  MT9T031_ROW_ADDRESS_MODE ; 
 int /*<<< orphan*/  MT9T031_ROW_START ; 
 int MT9T031_VERTICAL_BLANK ; 
 int /*<<< orphan*/  MT9T031_VERTICAL_BLANKING ; 
 int /*<<< orphan*/  MT9T031_WINDOW_HEIGHT ; 
 int /*<<< orphan*/  MT9T031_WINDOW_WIDTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int min (int,int) ; 
 struct v4l2_queryctrl* mt9t031_controls ; 
 int reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int const) ; 
 int roundup (int /*<<< orphan*/ ,int) ; 
 int set_shutter (struct i2c_client*,unsigned int) ; 
 struct mt9t031* to_mt9t031 (struct i2c_client*) ; 

__attribute__((used)) static int mt9t031_set_params(struct i2c_client *client,
			      struct v4l2_rect *rect, u16 xskip, u16 yskip)
{
	struct mt9t031 *mt9t031 = to_mt9t031(client);
	int ret;
	u16 xbin, ybin;
	const u16 hblank = MT9T031_HORIZONTAL_BLANK,
		vblank = MT9T031_VERTICAL_BLANK;

	xbin = min(xskip, (u16)3);
	ybin = min(yskip, (u16)3);

	/*
	 * Could just do roundup(rect->left, [xy]bin * 2); but this is cheaper.
	 * There is always a valid suitably aligned value. The worst case is
	 * xbin = 3, width = 2048. Then we will start at 36, the last read out
	 * pixel will be 2083, which is < 2085 - first black pixel.
	 *
	 * MT9T031 datasheet imposes window left border alignment, depending on
	 * the selected xskip. Failing to conform to this requirement produces
	 * dark horizontal stripes in the image. However, even obeying to this
	 * requirement doesn't eliminate the stripes in all configurations. They
	 * appear "locally reproducibly," but can differ between tests under
	 * different lighting conditions.
	 */
	switch (xbin) {
	case 1:
		rect->left &= ~1;
		break;
	case 2:
		rect->left &= ~3;
		break;
	case 3:
		rect->left = rect->left > roundup(MT9T031_COLUMN_SKIP, 6) ?
			(rect->left / 6) * 6 : roundup(MT9T031_COLUMN_SKIP, 6);
	}

	rect->top &= ~1;

	dev_dbg(&client->dev, "skip %u:%u, rect %ux%u@%u:%u\n",
		xskip, yskip, rect->width, rect->height, rect->left, rect->top);

	/* Disable register update, reconfigure atomically */
	ret = reg_set(client, MT9T031_OUTPUT_CONTROL, 1);
	if (ret < 0)
		return ret;

	/* Blanking and start values - default... */
	ret = reg_write(client, MT9T031_HORIZONTAL_BLANKING, hblank);
	if (ret >= 0)
		ret = reg_write(client, MT9T031_VERTICAL_BLANKING, vblank);

	if (yskip != mt9t031->yskip || xskip != mt9t031->xskip) {
		/* Binning, skipping */
		if (ret >= 0)
			ret = reg_write(client, MT9T031_COLUMN_ADDRESS_MODE,
					((xbin - 1) << 4) | (xskip - 1));
		if (ret >= 0)
			ret = reg_write(client, MT9T031_ROW_ADDRESS_MODE,
					((ybin - 1) << 4) | (yskip - 1));
	}
	dev_dbg(&client->dev, "new physical left %u, top %u\n",
		rect->left, rect->top);

	/*
	 * The caller provides a supported format, as guaranteed by
	 * icd->try_fmt_cap(), soc_camera_s_crop() and soc_camera_cropcap()
	 */
	if (ret >= 0)
		ret = reg_write(client, MT9T031_COLUMN_START, rect->left);
	if (ret >= 0)
		ret = reg_write(client, MT9T031_ROW_START, rect->top);
	if (ret >= 0)
		ret = reg_write(client, MT9T031_WINDOW_WIDTH, rect->width - 1);
	if (ret >= 0)
		ret = reg_write(client, MT9T031_WINDOW_HEIGHT,
				rect->height + mt9t031->y_skip_top - 1);
	if (ret >= 0 && mt9t031->autoexposure) {
		unsigned int total_h = rect->height + mt9t031->y_skip_top + vblank;
		ret = set_shutter(client, total_h);
		if (ret >= 0) {
			const u32 shutter_max = MT9T031_MAX_HEIGHT + vblank;
			const struct v4l2_queryctrl *qctrl =
				&mt9t031_controls[MT9T031_CTRL_EXPOSURE];
			mt9t031->exposure = (shutter_max / 2 + (total_h - 1) *
				 (qctrl->maximum - qctrl->minimum)) /
				shutter_max + qctrl->minimum;
		}
	}

	/* Re-enable register update, commit all changes */
	if (ret >= 0)
		ret = reg_clear(client, MT9T031_OUTPUT_CONTROL, 1);

	if (ret >= 0) {
		mt9t031->rect = *rect;
		mt9t031->xskip = xskip;
		mt9t031->yskip = yskip;
	}

	return ret < 0 ? ret : 0;
}