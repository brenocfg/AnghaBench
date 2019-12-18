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
struct pnp_dev {int dummy; } ;
struct ene_device {int /*<<< orphan*/  rdev; int /*<<< orphan*/  hw_io; int /*<<< orphan*/  irq; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_IO_SIZE ; 
 int /*<<< orphan*/  ene_rx_disable (struct ene_device*) ; 
 int /*<<< orphan*/  ene_rx_restore_hw_buffer (struct ene_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ene_device*) ; 
 int /*<<< orphan*/  kfree (struct ene_device*) ; 
 struct ene_device* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ene_remove(struct pnp_dev *pnp_dev)
{
	struct ene_device *dev = pnp_get_drvdata(pnp_dev);
	unsigned long flags;

	spin_lock_irqsave(&dev->hw_lock, flags);
	ene_rx_disable(dev);
	ene_rx_restore_hw_buffer(dev);
	spin_unlock_irqrestore(&dev->hw_lock, flags);

	free_irq(dev->irq, dev);
	release_region(dev->hw_io, ENE_IO_SIZE);
	rc_unregister_device(dev->rdev);
	kfree(dev);
}