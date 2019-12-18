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
struct soc_camera_link {int dummy; } ;
struct soc_camera_device {int /*<<< orphan*/ * ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct mt9m001 {int autoexposure; TYPE_1__ rect; scalar_t__ y_skip_top; int /*<<< orphan*/  subdev; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; struct soc_camera_device* platform_data; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  MT9M001_COLUMN_SKIP ; 
 int /*<<< orphan*/  MT9M001_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9M001_MAX_WIDTH ; 
 int /*<<< orphan*/  MT9M001_ROW_SKIP ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mt9m001*) ; 
 struct mt9m001* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m001_ops ; 
 int /*<<< orphan*/  mt9m001_subdev_ops ; 
 int mt9m001_video_probe (struct soc_camera_device*,struct i2c_client*) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 struct soc_camera_link* to_soc_camera_link (struct soc_camera_device*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m001_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct mt9m001 *mt9m001;
	struct soc_camera_device *icd = client->dev.platform_data;
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct soc_camera_link *icl;
	int ret;

	if (!icd) {
		dev_err(&client->dev, "MT9M001: missing soc-camera data!\n");
		return -EINVAL;
	}

	icl = to_soc_camera_link(icd);
	if (!icl) {
		dev_err(&client->dev, "MT9M001 driver needs platform data\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		return -EIO;
	}

	mt9m001 = kzalloc(sizeof(struct mt9m001), GFP_KERNEL);
	if (!mt9m001)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&mt9m001->subdev, client, &mt9m001_subdev_ops);

	/* Second stage probe - when a capture adapter is there */
	icd->ops		= &mt9m001_ops;

	mt9m001->y_skip_top	= 0;
	mt9m001->rect.left	= MT9M001_COLUMN_SKIP;
	mt9m001->rect.top	= MT9M001_ROW_SKIP;
	mt9m001->rect.width	= MT9M001_MAX_WIDTH;
	mt9m001->rect.height	= MT9M001_MAX_HEIGHT;

	/*
	 * Simulated autoexposure. If enabled, we calculate shutter width
	 * ourselves in the driver based on vertical blanking and frame width
	 */
	mt9m001->autoexposure = 1;

	ret = mt9m001_video_probe(icd, client);
	if (ret) {
		icd->ops = NULL;
		kfree(mt9m001);
	}

	return ret;
}