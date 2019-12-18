#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {scalar_t__ top; scalar_t__ left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_crop {struct v4l2_rect c; } ;
struct tw9910_priv {TYPE_3__* scale; TYPE_2__* info; } ;
struct soc_camera_device {int dummy; } ;
struct TYPE_5__ {struct soc_camera_device* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {scalar_t__ buswidth; int mpout; } ;

/* Variables and functions */
 int EINVAL ; 
 int LEN ; 
 int /*<<< orphan*/  OPFORM ; 
 int RTSEL_DET50 ; 
 int RTSEL_FIELD ; 
 int RTSEL_HLOCK ; 
 int RTSEL_MASK ; 
 int RTSEL_MONO ; 
 int RTSEL_RTCO ; 
 int RTSEL_SLOCK ; 
 int RTSEL_VLOCK ; 
 int RTSEL_VLOSS ; 
 scalar_t__ SOCAM_DATAWIDTH_16 ; 
#define  TW9910_MPO_DET50 135 
#define  TW9910_MPO_FIELD 134 
#define  TW9910_MPO_HLOCK 133 
#define  TW9910_MPO_MONO 132 
#define  TW9910_MPO_RTCO 131 
#define  TW9910_MPO_SLOCK 130 
#define  TW9910_MPO_VLOCK 129 
#define  TW9910_MPO_VLOSS 128 
 int /*<<< orphan*/  VBICNTL ; 
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 
 int /*<<< orphan*/  tw9910_hsync_ctrl ; 
 int tw9910_mask_set (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tw9910_reset (struct i2c_client*) ; 
 TYPE_3__* tw9910_select_norm (struct soc_camera_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tw9910_set_hsync (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int tw9910_set_scale (struct i2c_client*,TYPE_3__*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tw9910_s_crop(struct v4l2_subdev *sd, struct v4l2_crop *a)
{
	struct v4l2_rect *rect = &a->c;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tw9910_priv *priv = to_tw9910(client);
	struct soc_camera_device *icd = client->dev.platform_data;
	int                 ret  = -EINVAL;
	u8                  val;

	/*
	 * select suitable norm
	 */
	priv->scale = tw9910_select_norm(icd, rect->width, rect->height);
	if (!priv->scale)
		goto tw9910_set_fmt_error;

	/*
	 * reset hardware
	 */
	tw9910_reset(client);

	/*
	 * set bus width
	 */
	val = 0x00;
	if (SOCAM_DATAWIDTH_16 == priv->info->buswidth)
		val = LEN;

	ret = tw9910_mask_set(client, OPFORM, LEN, val);
	if (ret < 0)
		goto tw9910_set_fmt_error;

	/*
	 * select MPOUT behavior
	 */
	switch (priv->info->mpout) {
	case TW9910_MPO_VLOSS:
		val = RTSEL_VLOSS; break;
	case TW9910_MPO_HLOCK:
		val = RTSEL_HLOCK; break;
	case TW9910_MPO_SLOCK:
		val = RTSEL_SLOCK; break;
	case TW9910_MPO_VLOCK:
		val = RTSEL_VLOCK; break;
	case TW9910_MPO_MONO:
		val = RTSEL_MONO;  break;
	case TW9910_MPO_DET50:
		val = RTSEL_DET50; break;
	case TW9910_MPO_FIELD:
		val = RTSEL_FIELD; break;
	case TW9910_MPO_RTCO:
		val = RTSEL_RTCO;  break;
	default:
		val = 0;
	}

	ret = tw9910_mask_set(client, VBICNTL, RTSEL_MASK, val);
	if (ret < 0)
		goto tw9910_set_fmt_error;

	/*
	 * set scale
	 */
	ret = tw9910_set_scale(client, priv->scale);
	if (ret < 0)
		goto tw9910_set_fmt_error;

	/*
	 * set hsync
	 */
	ret = tw9910_set_hsync(client, &tw9910_hsync_ctrl);
	if (ret < 0)
		goto tw9910_set_fmt_error;

	rect->width = priv->scale->width;
	rect->height = priv->scale->height;
	rect->left = 0;
	rect->top = 0;

	return ret;

tw9910_set_fmt_error:

	tw9910_reset(client);
	priv->scale = NULL;

	return ret;
}