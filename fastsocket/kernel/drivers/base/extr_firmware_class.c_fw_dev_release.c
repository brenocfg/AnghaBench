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
struct firmware_priv {int nr_pages; struct firmware_priv* fw_id; struct firmware_priv* pages; } ;
struct device {int nr_pages; struct device* fw_id; struct device* pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __free_page (struct firmware_priv) ; 
 struct firmware_priv* dev_get_drvdata (struct firmware_priv*) ; 
 int /*<<< orphan*/  kfree (struct firmware_priv*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fw_dev_release(struct device *dev)
{
	struct firmware_priv *fw_priv = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < fw_priv->nr_pages; i++)
		__free_page(fw_priv->pages[i]);
	kfree(fw_priv->pages);
	kfree(fw_priv->fw_id);
	kfree(fw_priv);
	kfree(dev);

	module_put(THIS_MODULE);
}