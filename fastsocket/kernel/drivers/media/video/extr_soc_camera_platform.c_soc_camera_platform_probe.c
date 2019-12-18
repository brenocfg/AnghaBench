#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct soc_camera_platform_priv {TYPE_1__ subdev; } ;
struct soc_camera_platform_info {int /*<<< orphan*/  dev; } ;
struct soc_camera_host {int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct soc_camera_device {int /*<<< orphan*/ * ops; TYPE_5__ dev; } ;
struct TYPE_11__ {struct soc_camera_platform_info* platform_data; } ;
struct platform_device {TYPE_6__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_NAME_SIZE ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_6__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  kfree (struct soc_camera_platform_priv*) ; 
 struct soc_camera_platform_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_subdev_ops ; 
 int /*<<< orphan*/  soc_camera_platform_ops ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct soc_camera_device* to_soc_camera_dev (int /*<<< orphan*/ ) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int v4l2_device_register_subdev (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_1__*,struct soc_camera_platform_info*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int soc_camera_platform_probe(struct platform_device *pdev)
{
	struct soc_camera_host *ici;
	struct soc_camera_platform_priv *priv;
	struct soc_camera_platform_info *p = pdev->dev.platform_data;
	struct soc_camera_device *icd;
	int ret;

	if (!p)
		return -EINVAL;

	if (!p->dev) {
		dev_err(&pdev->dev,
			"Platform has not set soc_camera_device pointer!\n");
		return -EINVAL;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	icd = to_soc_camera_dev(p->dev);

	/* soc-camera convention: control's drvdata points to the subdev */
	platform_set_drvdata(pdev, &priv->subdev);
	/* Set the control device reference */
	dev_set_drvdata(&icd->dev, &pdev->dev);

	icd->ops = &soc_camera_platform_ops;

	ici = to_soc_camera_host(icd->dev.parent);

	v4l2_subdev_init(&priv->subdev, &platform_subdev_ops);
	v4l2_set_subdevdata(&priv->subdev, p);
	strncpy(priv->subdev.name, dev_name(&pdev->dev), V4L2_SUBDEV_NAME_SIZE);

	ret = v4l2_device_register_subdev(&ici->v4l2_dev, &priv->subdev);
	if (ret)
		goto evdrs;

	return ret;

evdrs:
	icd->ops = NULL;
	platform_set_drvdata(pdev, NULL);
	kfree(priv);
	return ret;
}