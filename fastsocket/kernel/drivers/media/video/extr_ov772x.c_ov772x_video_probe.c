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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {scalar_t__ iface; TYPE_1__ dev; } ;
struct ov772x_priv {int /*<<< orphan*/  model; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ nr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MIDH ; 
 int /*<<< orphan*/  MIDL ; 
#define  OV7720 129 
#define  OV7725 128 
 int /*<<< orphan*/  PID ; 
 int /*<<< orphan*/  V4L2_IDENT_OV7720 ; 
 int /*<<< orphan*/  V4L2_IDENT_OV7725 ; 
 int /*<<< orphan*/  VER ; 
 int VERSION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct ov772x_priv* to_ov772x (struct i2c_client*) ; 
 TYPE_2__* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov772x_video_probe(struct soc_camera_device *icd,
			      struct i2c_client *client)
{
	struct ov772x_priv *priv = to_ov772x(client);
	u8                  pid, ver;
	const char         *devname;

	/*
	 * We must have a parent by now. And it cannot be a wrong one.
	 * So this entire test is completely redundant.
	 */
	if (!icd->dev.parent ||
	    to_soc_camera_host(icd->dev.parent)->nr != icd->iface)
		return -ENODEV;

	/*
	 * check and show product ID and manufacturer ID
	 */
	pid = i2c_smbus_read_byte_data(client, PID);
	ver = i2c_smbus_read_byte_data(client, VER);

	switch (VERSION(pid, ver)) {
	case OV7720:
		devname     = "ov7720";
		priv->model = V4L2_IDENT_OV7720;
		break;
	case OV7725:
		devname     = "ov7725";
		priv->model = V4L2_IDENT_OV7725;
		break;
	default:
		dev_err(&client->dev,
			"Product ID error %x:%x\n", pid, ver);
		return -ENODEV;
	}

	dev_info(&client->dev,
		 "%s Product ID %0x:%0x Manufacturer ID %x:%x\n",
		 devname,
		 pid,
		 ver,
		 i2c_smbus_read_byte_data(client, MIDH),
		 i2c_smbus_read_byte_data(client, MIDL));

	return 0;
}