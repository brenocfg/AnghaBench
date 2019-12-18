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
struct atm_dev {int /*<<< orphan*/  proc_name; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  atm_proc_root ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void atm_proc_dev_deregister(struct atm_dev *dev)
{
	if (!dev->ops->proc_read)
		return;

	remove_proc_entry(dev->proc_name, atm_proc_root);
	kfree(dev->proc_name);
}