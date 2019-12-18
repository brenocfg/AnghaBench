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
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBALENABLE ; 
 int /*<<< orphan*/  SGE_CONTROL ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  t4_intr_disable (struct adapter*) ; 
 int /*<<< orphan*/  t4_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void t4_fatal_err(struct adapter *adap)
{
	t4_set_reg_field(adap, SGE_CONTROL, GLOBALENABLE, 0);
	t4_intr_disable(adap);
	dev_alert(adap->pdev_dev, "encountered fatal error, adapter stopped\n");
}