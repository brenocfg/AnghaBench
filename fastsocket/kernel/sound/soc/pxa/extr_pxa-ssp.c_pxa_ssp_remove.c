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
struct TYPE_2__ {int /*<<< orphan*/  ssp; } ;
struct ssp_priv {TYPE_1__ dev; } ;
struct snd_soc_dai {struct ssp_priv* private_data; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ssp_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa_ssp_remove(struct platform_device *pdev,
			      struct snd_soc_dai *dai)
{
	struct ssp_priv *priv = dai->private_data;
	ssp_free(priv->dev.ssp);
}