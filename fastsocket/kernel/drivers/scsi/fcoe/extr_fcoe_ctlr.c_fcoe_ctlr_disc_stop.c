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
struct fcoe_ctlr {int /*<<< orphan*/  ctlr_mutex; } ;
struct TYPE_2__ {struct fcoe_ctlr* priv; } ;
struct fc_lport {TYPE_1__ disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcoe_ctlr_disc_stop_locked (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fcoe_ctlr_disc_stop(struct fc_lport *lport)
{
	struct fcoe_ctlr *fip = lport->disc.priv;

	mutex_lock(&fip->ctlr_mutex);
	fcoe_ctlr_disc_stop_locked(lport);
	mutex_unlock(&fip->ctlr_mutex);
}