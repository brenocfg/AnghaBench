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
struct vio_dev {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vio_dev* vio_find_node (struct device_node*) ; 
 int /*<<< orphan*/  vio_unregister_device (struct vio_dev*) ; 

__attribute__((used)) static int dlpar_remove_vio_slot(char *drc_name, struct device_node *dn)
{
	struct vio_dev *vio_dev;

	vio_dev = vio_find_node(dn);
	if (!vio_dev)
		return -EINVAL;

	vio_unregister_device(vio_dev);
	return 0;
}