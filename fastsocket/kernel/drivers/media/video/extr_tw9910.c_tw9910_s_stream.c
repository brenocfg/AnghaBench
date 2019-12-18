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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct tw9910_priv {int revision; TYPE_1__* scale; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  OEN_TRI_SEL_ALL_OFF_r0 ; 
 int /*<<< orphan*/  OEN_TRI_SEL_ALL_OFF_r1 ; 
 int /*<<< orphan*/  OEN_TRI_SEL_ALL_ON ; 
 int /*<<< orphan*/  OEN_TRI_SEL_MASK ; 
 int /*<<< orphan*/  OPFORM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tw9910_priv* to_tw9910 (struct i2c_client*) ; 
 int tw9910_mask_set (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tw9910_power (struct i2c_client*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tw9910_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct tw9910_priv *priv = to_tw9910(client);
	u8 val;
	int ret;

	if (!enable) {
		switch (priv->revision) {
		case 0:
			val = OEN_TRI_SEL_ALL_OFF_r0;
			break;
		case 1:
			val = OEN_TRI_SEL_ALL_OFF_r1;
			break;
		default:
			dev_err(&client->dev, "un-supported revision\n");
			return -EINVAL;
		}
	} else {
		val = OEN_TRI_SEL_ALL_ON;

		if (!priv->scale) {
			dev_err(&client->dev, "norm select error\n");
			return -EPERM;
		}

		dev_dbg(&client->dev, "%s %dx%d\n",
			priv->scale->name,
			priv->scale->width,
			priv->scale->height);
	}

	ret = tw9910_mask_set(client, OPFORM, OEN_TRI_SEL_MASK, val);
	if (ret < 0)
		return ret;

	return tw9910_power(client, enable);
}