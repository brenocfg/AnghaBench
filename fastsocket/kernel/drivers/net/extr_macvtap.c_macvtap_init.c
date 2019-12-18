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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACVTAP_NUM_DEVS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ ) ; 
 int macvlan_link_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macvtap_cdev ; 
 int /*<<< orphan*/  macvtap_class ; 
 int /*<<< orphan*/  macvtap_fops ; 
 int /*<<< orphan*/  macvtap_link_ops ; 
 int /*<<< orphan*/  macvtap_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macvtap_init(void)
{
	int err;

	err = alloc_chrdev_region(&macvtap_major, 0,
				MACVTAP_NUM_DEVS, "macvtap");
	if (err)
		goto out1;

	cdev_init(&macvtap_cdev, &macvtap_fops);
	err = cdev_add(&macvtap_cdev, macvtap_major, MACVTAP_NUM_DEVS);
	if (err)
		goto out2;

	macvtap_class = class_create(THIS_MODULE, "macvtap");
	if (IS_ERR(macvtap_class)) {
		err = PTR_ERR(macvtap_class);
		goto out3;
	}

	err = macvlan_link_register(&macvtap_link_ops);
	if (err)
		goto out4;

	return 0;

out4:
	class_unregister(macvtap_class);
out3:
	cdev_del(&macvtap_cdev);
out2:
	unregister_chrdev_region(macvtap_major, MACVTAP_NUM_DEVS);
out1:
	return err;
}