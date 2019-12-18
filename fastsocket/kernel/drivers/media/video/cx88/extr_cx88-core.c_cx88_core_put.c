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
struct pci_dev {int dummy; } ;
struct cx88_core {scalar_t__ i2c_rc; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  lmmio; int /*<<< orphan*/  devlist; int /*<<< orphan*/  i2c_adap; scalar_t__ i2c_rtc; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx88_devcount ; 
 int /*<<< orphan*/  cx88_ir_fini (struct cx88_core*) ; 
 int /*<<< orphan*/  devlist ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cx88_core*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

void cx88_core_put(struct cx88_core *core, struct pci_dev *pci)
{
	release_mem_region(pci_resource_start(pci,0),
			   pci_resource_len(pci,0));

	if (!atomic_dec_and_test(&core->refcount))
		return;

	mutex_lock(&devlist);
	cx88_ir_fini(core);
	if (0 == core->i2c_rc) {
		if (core->i2c_rtc)
			i2c_unregister_device(core->i2c_rtc);
		i2c_del_adapter(&core->i2c_adap);
	}
	list_del(&core->devlist);
	iounmap(core->lmmio);
	cx88_devcount--;
	mutex_unlock(&devlist);
	v4l2_device_unregister(&core->v4l2_dev);
	kfree(core);
}