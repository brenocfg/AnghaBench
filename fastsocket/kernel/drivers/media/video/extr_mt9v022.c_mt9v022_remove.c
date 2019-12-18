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
struct soc_camera_device {int /*<<< orphan*/ * ops; } ;
struct mt9v022 {int dummy; } ;
struct TYPE_2__ {struct soc_camera_device* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mt9v022*) ; 
 int /*<<< orphan*/  mt9v022_video_remove (struct soc_camera_device*) ; 
 struct mt9v022* to_mt9v022 (struct i2c_client*) ; 

__attribute__((used)) static int mt9v022_remove(struct i2c_client *client)
{
	struct mt9v022 *mt9v022 = to_mt9v022(client);
	struct soc_camera_device *icd = client->dev.platform_data;

	icd->ops = NULL;
	mt9v022_video_remove(icd);
	kfree(mt9v022);

	return 0;
}