#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sata_fsl_host_priv {int /*<<< orphan*/  hcr_base; int /*<<< orphan*/  irq; } ;
struct of_device {int /*<<< orphan*/  dev; } ;
struct ata_host {struct sata_fsl_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_host_detach (struct ata_host*) ; 
 struct ata_host* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sata_fsl_host_priv*) ; 

__attribute__((used)) static int sata_fsl_remove(struct of_device *ofdev)
{
	struct ata_host *host = dev_get_drvdata(&ofdev->dev);
	struct sata_fsl_host_priv *host_priv = host->private_data;

	ata_host_detach(host);

	dev_set_drvdata(&ofdev->dev, NULL);

	irq_dispose_mapping(host_priv->irq);
	iounmap(host_priv->hcr_base);
	kfree(host_priv);

	return 0;
}