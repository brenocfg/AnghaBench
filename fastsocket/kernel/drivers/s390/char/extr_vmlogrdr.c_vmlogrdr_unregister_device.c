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
struct vmlogrdr_priv_t {TYPE_1__* device; int /*<<< orphan*/  minor_num; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmlogrdr_attr_group ; 
 int /*<<< orphan*/  vmlogrdr_class ; 
 int /*<<< orphan*/  vmlogrdr_major ; 

__attribute__((used)) static int vmlogrdr_unregister_device(struct vmlogrdr_priv_t *priv)
{
	device_destroy(vmlogrdr_class, MKDEV(vmlogrdr_major, priv->minor_num));
	if (priv->device != NULL) {
		sysfs_remove_group(&priv->device->kobj, &vmlogrdr_attr_group);
		device_unregister(priv->device);
		priv->device=NULL;
	}
	return 0;
}