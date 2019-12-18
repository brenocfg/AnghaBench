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
struct pnp_dev {int /*<<< orphan*/  card_list; int /*<<< orphan*/ * card; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pnp_remove_device (struct pnp_dev*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnp_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pnp_remove_card_device(struct pnp_dev *dev)
{
	spin_lock(&pnp_lock);
	dev->card = NULL;
	list_del(&dev->card_list);
	spin_unlock(&pnp_lock);
	__pnp_remove_device(dev);
}