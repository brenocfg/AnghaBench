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
struct se_device {int dev_reservation_flags; int /*<<< orphan*/  dev_reservation_lock; TYPE_1__* transport; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ transport_type; } ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS ; 
 scalar_t__ TRANSPORT_PLUGIN_PHBA_PDEV ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*) ; 
 int target_core_dev_pr_show_spc2_res (struct se_device*,char*) ; 
 int target_core_dev_pr_show_spc3_res (struct se_device*,char*) ; 

__attribute__((used)) static ssize_t target_core_dev_pr_show_attr_res_holder(struct se_device *dev,
		char *page)
{
	int ret;

	if (dev->transport->transport_type == TRANSPORT_PLUGIN_PHBA_PDEV)
		return sprintf(page, "Passthrough\n");

	spin_lock(&dev->dev_reservation_lock);
	if (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		ret = target_core_dev_pr_show_spc2_res(dev, page);
	else
		ret = target_core_dev_pr_show_spc3_res(dev, page);
	spin_unlock(&dev->dev_reservation_lock);
	return ret;
}