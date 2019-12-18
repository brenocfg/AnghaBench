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
struct TYPE_2__ {int /*<<< orphan*/ * ssp; } ;
struct ssp_priv {unsigned int dai_fmt; TYPE_1__ dev; } ;
struct snd_soc_dai {struct ssp_priv* private_data; scalar_t__ id; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ssp_priv*) ; 
 struct ssp_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ssp_request (scalar_t__,char*) ; 

__attribute__((used)) static int pxa_ssp_probe(struct platform_device *pdev,
			    struct snd_soc_dai *dai)
{
	struct ssp_priv *priv;
	int ret;

	priv = kzalloc(sizeof(struct ssp_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev.ssp = ssp_request(dai->id + 1, "SoC audio");
	if (priv->dev.ssp == NULL) {
		ret = -ENODEV;
		goto err_priv;
	}

	priv->dai_fmt = (unsigned int) -1;
	dai->private_data = priv;

	return 0;

err_priv:
	kfree(priv);
	return ret;
}