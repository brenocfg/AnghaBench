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
struct orinoco_private {struct airport* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct macio_dev {TYPE_1__ ofdev; } ;
struct airport {int /*<<< orphan*/ * vaddr; scalar_t__ irq_requested; int /*<<< orphan*/  irq; scalar_t__ ndev_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAC_FTR_AIRPORT_ENABLE ; 
 struct orinoco_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct orinoco_private*) ; 
 int /*<<< orphan*/  free_orinocodev (struct orinoco_private*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macio_get_of_node (struct macio_dev*) ; 
 int /*<<< orphan*/  macio_release_resource (struct macio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_set_drvdata (struct macio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  orinoco_if_del (struct orinoco_private*) ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static int
airport_detach(struct macio_dev *mdev)
{
	struct orinoco_private *priv = dev_get_drvdata(&mdev->ofdev.dev);
	struct airport *card = priv->card;

	if (card->ndev_registered)
		orinoco_if_del(priv);
	card->ndev_registered = 0;

	if (card->irq_requested)
		free_irq(card->irq, priv);
	card->irq_requested = 0;

	if (card->vaddr)
		iounmap(card->vaddr);
	card->vaddr = NULL;

	macio_release_resource(mdev, 0);

	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(mdev), 0, 0);
	ssleep(1);

	macio_set_drvdata(mdev, NULL);
	free_orinocodev(priv);

	return 0;
}