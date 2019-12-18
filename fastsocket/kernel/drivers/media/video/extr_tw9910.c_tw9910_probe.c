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
struct tw9910_video_info {int dummy; } ;
struct tw9910_priv {int /*<<< orphan*/  subdev; struct tw9910_video_info* info; } ;
struct soc_camera_link {int /*<<< orphan*/  bus_id; struct tw9910_video_info* priv; } ;
struct soc_camera_device {int /*<<< orphan*/ * ops; int /*<<< orphan*/  iface; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; struct soc_camera_device* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tw9910_priv*) ; 
 struct tw9910_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 struct soc_camera_link* to_soc_camera_link (struct soc_camera_device*) ; 
 int /*<<< orphan*/  tw9910_ops ; 
 int /*<<< orphan*/  tw9910_subdev_ops ; 
 int tw9910_video_probe (struct soc_camera_device*,struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tw9910_probe(struct i2c_client *client,
			const struct i2c_device_id *did)

{
	struct tw9910_priv             *priv;
	struct tw9910_video_info       *info;
	struct soc_camera_device       *icd = client->dev.platform_data;
	struct i2c_adapter             *adapter =
		to_i2c_adapter(client->dev.parent);
	struct soc_camera_link         *icl;
	int                             ret;

	if (!icd) {
		dev_err(&client->dev, "TW9910: missing soc-camera data!\n");
		return -EINVAL;
	}

	icl = to_soc_camera_link(icd);
	if (!icl || !icl->priv)
		return -EINVAL;

	info = icl->priv;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev,
			"I2C-Adapter doesn't support "
			"I2C_FUNC_SMBUS_BYTE_DATA\n");
		return -EIO;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info   = info;

	v4l2_i2c_subdev_init(&priv->subdev, client, &tw9910_subdev_ops);

	icd->ops     = &tw9910_ops;
	icd->iface   = icl->bus_id;

	ret = tw9910_video_probe(icd, client);
	if (ret) {
		icd->ops = NULL;
		kfree(priv);
	}

	return ret;
}