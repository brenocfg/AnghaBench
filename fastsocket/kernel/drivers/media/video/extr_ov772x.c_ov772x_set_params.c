#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ov772x_priv {int band_filter; TYPE_4__* cfmt; TYPE_3__* win; scalar_t__ flag_hflip; scalar_t__ flag_vflip; TYPE_2__* info; } ;
struct i2c_client {int dummy; } ;
typedef  enum v4l2_mbus_pixelcode { ____Placeholder_v4l2_mbus_pixelcode } v4l2_mbus_pixelcode ;
struct TYPE_9__ {int code; int dsp3; int com3; int com7; } ;
struct TYPE_8__ {int com7_bit; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  regs; } ;
struct TYPE_6__ {int strength; int threshold; int upper; int lower; } ;
struct TYPE_7__ {int flags; TYPE_1__ edgectrl; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  BDBASE ; 
 int BNDF_ON_OFF ; 
 int /*<<< orphan*/  COM3 ; 
 int /*<<< orphan*/  COM7 ; 
 int /*<<< orphan*/  COM8 ; 
 int /*<<< orphan*/  DSPAUTO ; 
 int /*<<< orphan*/  DSP_CTRL3 ; 
 int EDGE_ACTRL ; 
 int /*<<< orphan*/  EDGE_LOWER ; 
 int EDGE_LOWER_MASK ; 
 int EDGE_STRENGTH_MASK ; 
 int /*<<< orphan*/  EDGE_STRNGT ; 
 int EDGE_THRESHOLD_MASK ; 
 int /*<<< orphan*/  EDGE_TRSHLD ; 
 int /*<<< orphan*/  EDGE_UPPER ; 
 int EDGE_UPPER_MASK ; 
 int EINVAL ; 
 int FMT_MASK ; 
 int HFLIP_IMG ; 
 int IMG_MASK ; 
 int OFMT_MASK ; 
 int OV772X_FLAG_HFLIP ; 
 int OV772X_FLAG_VFLIP ; 
 int OV772X_MANUAL_EDGE_CTRL ; 
 int SLCT_MASK ; 
 int SWAP_MASK ; 
 int UV_MASK ; 
 int VFLIP_IMG ; 
 TYPE_4__* ov772x_cfmts ; 
 int ov772x_mask_set (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ov772x_reset (struct i2c_client*) ; 
 TYPE_3__* ov772x_select_win (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ov772x_write_array (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct ov772x_priv* to_ov772x (struct i2c_client*) ; 

__attribute__((used)) static int ov772x_set_params(struct i2c_client *client, u32 *width, u32 *height,
			     enum v4l2_mbus_pixelcode code)
{
	struct ov772x_priv *priv = to_ov772x(client);
	int ret = -EINVAL;
	u8  val;
	int i;

	/*
	 * select format
	 */
	priv->cfmt = NULL;
	for (i = 0; i < ARRAY_SIZE(ov772x_cfmts); i++) {
		if (code == ov772x_cfmts[i].code) {
			priv->cfmt = ov772x_cfmts + i;
			break;
		}
	}
	if (!priv->cfmt)
		goto ov772x_set_fmt_error;

	/*
	 * select win
	 */
	priv->win = ov772x_select_win(*width, *height);

	/*
	 * reset hardware
	 */
	ov772x_reset(client);

	/*
	 * Edge Ctrl
	 */
	if (priv->info->edgectrl.strength & OV772X_MANUAL_EDGE_CTRL) {

		/*
		 * Manual Edge Control Mode
		 *
		 * Edge auto strength bit is set by default.
		 * Remove it when manual mode.
		 */

		ret = ov772x_mask_set(client, DSPAUTO, EDGE_ACTRL, 0x00);
		if (ret < 0)
			goto ov772x_set_fmt_error;

		ret = ov772x_mask_set(client,
				      EDGE_TRSHLD, EDGE_THRESHOLD_MASK,
				      priv->info->edgectrl.threshold);
		if (ret < 0)
			goto ov772x_set_fmt_error;

		ret = ov772x_mask_set(client,
				      EDGE_STRNGT, EDGE_STRENGTH_MASK,
				      priv->info->edgectrl.strength);
		if (ret < 0)
			goto ov772x_set_fmt_error;

	} else if (priv->info->edgectrl.upper > priv->info->edgectrl.lower) {
		/*
		 * Auto Edge Control Mode
		 *
		 * set upper and lower limit
		 */
		ret = ov772x_mask_set(client,
				      EDGE_UPPER, EDGE_UPPER_MASK,
				      priv->info->edgectrl.upper);
		if (ret < 0)
			goto ov772x_set_fmt_error;

		ret = ov772x_mask_set(client,
				      EDGE_LOWER, EDGE_LOWER_MASK,
				      priv->info->edgectrl.lower);
		if (ret < 0)
			goto ov772x_set_fmt_error;
	}

	/*
	 * set size format
	 */
	ret = ov772x_write_array(client, priv->win->regs);
	if (ret < 0)
		goto ov772x_set_fmt_error;

	/*
	 * set DSP_CTRL3
	 */
	val = priv->cfmt->dsp3;
	if (val) {
		ret = ov772x_mask_set(client,
				      DSP_CTRL3, UV_MASK, val);
		if (ret < 0)
			goto ov772x_set_fmt_error;
	}

	/*
	 * set COM3
	 */
	val = priv->cfmt->com3;
	if (priv->info->flags & OV772X_FLAG_VFLIP)
		val |= VFLIP_IMG;
	if (priv->info->flags & OV772X_FLAG_HFLIP)
		val |= HFLIP_IMG;
	if (priv->flag_vflip)
		val ^= VFLIP_IMG;
	if (priv->flag_hflip)
		val ^= HFLIP_IMG;

	ret = ov772x_mask_set(client,
			      COM3, SWAP_MASK | IMG_MASK, val);
	if (ret < 0)
		goto ov772x_set_fmt_error;

	/*
	 * set COM7
	 */
	val = priv->win->com7_bit | priv->cfmt->com7;
	ret = ov772x_mask_set(client,
			      COM7, SLCT_MASK | FMT_MASK | OFMT_MASK,
			      val);
	if (ret < 0)
		goto ov772x_set_fmt_error;

	/*
	 * set COM8
	 */
	if (priv->band_filter) {
		ret = ov772x_mask_set(client, COM8, BNDF_ON_OFF, 1);
		if (!ret)
			ret = ov772x_mask_set(client, BDBASE,
					      0xff, 256 - priv->band_filter);
		if (ret < 0)
			goto ov772x_set_fmt_error;
	}

	*width = priv->win->width;
	*height = priv->win->height;

	return ret;

ov772x_set_fmt_error:

	ov772x_reset(client);
	priv->win = NULL;
	priv->cfmt = NULL;

	return ret;
}