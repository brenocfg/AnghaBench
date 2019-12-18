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
struct firedtv {int /*<<< orphan*/  list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct firedtv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fdtv_dvb_unregister (struct firedtv*) ; 
 int /*<<< orphan*/  fdtv_unregister_rc (struct firedtv*) ; 
 int /*<<< orphan*/  kfree (struct firedtv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  node_list_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int node_remove(struct device *dev)
{
	struct firedtv *fdtv = dev_get_drvdata(dev);

	fdtv_dvb_unregister(fdtv);

	spin_lock_irq(&node_list_lock);
	list_del(&fdtv->list);
	spin_unlock_irq(&node_list_lock);

	fdtv_unregister_rc(fdtv);

	kfree(fdtv);
	return 0;
}