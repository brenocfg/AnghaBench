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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bcma_sflash {int /*<<< orphan*/  size; int /*<<< orphan*/  numblocks; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  window; struct bcm47xxsflash* priv; } ;
struct bcm47xxsflash {int /*<<< orphan*/  mtd; int /*<<< orphan*/  size; int /*<<< orphan*/  numblocks; int /*<<< orphan*/  blocksize; int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm47xxsflash_fill_mtd (struct bcm47xxsflash*) ; 
 struct bcma_sflash* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct bcm47xxsflash* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mtd_device_parse_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  probes ; 

__attribute__((used)) static int bcm47xxsflash_probe(struct platform_device *pdev)
{
	struct bcma_sflash *sflash = dev_get_platdata(&pdev->dev);
	struct bcm47xxsflash *b47s;
	int err;

	b47s = kzalloc(sizeof(*b47s), GFP_KERNEL);
	if (!b47s) {
		err = -ENOMEM;
		goto out;
	}
	sflash->priv = b47s;

	b47s->window = sflash->window;
	b47s->blocksize = sflash->blocksize;
	b47s->numblocks = sflash->numblocks;
	b47s->size = sflash->size;
	bcm47xxsflash_fill_mtd(b47s);

	err = mtd_device_parse_register(&b47s->mtd, probes, NULL, NULL, 0);
	if (err) {
		pr_err("Failed to register MTD device: %d\n", err);
		goto err_dev_reg;
	}

	return 0;

err_dev_reg:
	kfree(&b47s->mtd);
out:
	return err;
}