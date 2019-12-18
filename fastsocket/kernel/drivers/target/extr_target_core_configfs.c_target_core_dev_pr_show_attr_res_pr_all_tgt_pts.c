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
struct se_device {int /*<<< orphan*/  dev_reservation_lock; TYPE_1__* dev_pr_res_holder; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ pr_reg_all_tg_pt; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t target_core_dev_pr_show_attr_res_pr_all_tgt_pts(
		struct se_device *dev, char *page)
{
	ssize_t len = 0;

	spin_lock(&dev->dev_reservation_lock);
	if (!dev->dev_pr_res_holder) {
		len = sprintf(page, "No SPC-3 Reservation holder\n");
	} else if (dev->dev_pr_res_holder->pr_reg_all_tg_pt) {
		len = sprintf(page, "SPC-3 Reservation: All Target"
			" Ports registration\n");
	} else {
		len = sprintf(page, "SPC-3 Reservation: Single"
			" Target Port registration\n");
	}

	spin_unlock(&dev->dev_reservation_lock);
	return len;
}