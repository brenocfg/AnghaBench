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
struct soc_camera_platform_priv {int /*<<< orphan*/  subdev; } ;
struct soc_camera_platform_info {int /*<<< orphan*/  dev; } ;
struct soc_camera_device {int /*<<< orphan*/ * ops; } ;
struct TYPE_2__ {struct soc_camera_platform_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct soc_camera_platform_priv* get_priv (struct platform_device*) ; 
 int /*<<< orphan*/  kfree (struct soc_camera_platform_priv*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 struct soc_camera_device* to_soc_camera_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int soc_camera_platform_remove(struct platform_device *pdev)
{
	struct soc_camera_platform_priv *priv = get_priv(pdev);
	struct soc_camera_platform_info *p = pdev->dev.platform_data;
	struct soc_camera_device *icd = to_soc_camera_dev(p->dev);

	v4l2_device_unregister_subdev(&priv->subdev);
	icd->ops = NULL;
	platform_set_drvdata(pdev, NULL);
	kfree(priv);
	return 0;
}