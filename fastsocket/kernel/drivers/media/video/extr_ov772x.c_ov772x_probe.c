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
struct soc_camera_link {int /*<<< orphan*/  priv; } ;
struct soc_camera_device {int /*<<< orphan*/ * ops; } ;
struct ov772x_priv {int /*<<< orphan*/  subdev; int /*<<< orphan*/  info; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; struct soc_camera_device* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct i2c_adapter {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ov772x_priv*) ; 
 struct ov772x_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov772x_ops ; 
 int /*<<< orphan*/  ov772x_subdev_ops ; 
 int ov772x_video_probe (struct soc_camera_device*,struct i2c_client*) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 struct soc_camera_link* to_soc_camera_link (struct soc_camera_device*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov772x_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct ov772x_priv        *priv;
	struct soc_camera_device  *icd = client->dev.platform_data;
	struct i2c_adapter        *adapter = to_i2c_adapter(client->dev.parent);
	struct soc_camera_link    *icl;
	int                        ret;

	if (!icd) {
		dev_err(&client->dev, "OV772X: missing soc-camera data!\n");
		return -EINVAL;
	}

	icl = to_soc_camera_link(icd);
	if (!icl || !icl->priv)
		return -EINVAL;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&adapter->dev,
			"I2C-Adapter doesn't support "
			"I2C_FUNC_SMBUS_BYTE_DATA\n");
		return -EIO;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info = icl->priv;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov772x_subdev_ops);

	icd->ops		= &ov772x_ops;

	ret = ov772x_video_probe(icd, client);
	if (ret) {
		icd->ops = NULL;
		kfree(priv);
	}

	return ret;
}