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
struct c2port_device {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  c2port_bin_attrs ; 
 int /*<<< orphan*/  c2port_class ; 
 int /*<<< orphan*/  c2port_idr ; 
 int /*<<< orphan*/  c2port_idr_lock ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c2port_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void c2port_device_unregister(struct c2port_device *c2dev)
{
	if (!c2dev)
		return;

	dev_info(c2dev->dev, "C2 port %s removed\n", c2dev->name);

	device_remove_bin_file(c2dev->dev, &c2port_bin_attrs);
	spin_lock_irq(&c2port_idr_lock);
	idr_remove(&c2port_idr, c2dev->id);
	spin_unlock_irq(&c2port_idr_lock);

	device_destroy(c2port_class, c2dev->id);

	kfree(c2dev);
}