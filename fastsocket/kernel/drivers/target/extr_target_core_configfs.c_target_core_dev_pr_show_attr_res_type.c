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
struct se_device {int dev_reservation_flags; TYPE_1__* transport; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ transport_type; } ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS ; 
 scalar_t__ TRANSPORT_PLUGIN_PHBA_PDEV ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t target_core_dev_pr_show_attr_res_type(
		struct se_device *dev, char *page)
{
	if (dev->transport->transport_type == TRANSPORT_PLUGIN_PHBA_PDEV)
		return sprintf(page, "SPC_PASSTHROUGH\n");
	else if (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)
		return sprintf(page, "SPC2_RESERVATIONS\n");
	else
		return sprintf(page, "SPC3_PERSISTENT_RESERVATIONS\n");
}