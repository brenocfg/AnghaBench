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
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  lp_mutex; } ;

/* Variables and functions */
 scalar_t__ LPORT_ST_DISABLED ; 
 scalar_t__ LPORT_ST_LOGO ; 
 int /*<<< orphan*/  LPORT_ST_RESET ; 
 int /*<<< orphan*/  fc_lport_enter_reset (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_state_enter (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int fc_fabric_login(struct fc_lport *lport)
{
	int rc = -1;

	mutex_lock(&lport->lp_mutex);
	if (lport->state == LPORT_ST_DISABLED ||
	    lport->state == LPORT_ST_LOGO) {
		fc_lport_state_enter(lport, LPORT_ST_RESET);
		fc_lport_enter_reset(lport);
		rc = 0;
	}
	mutex_unlock(&lport->lp_mutex);

	return rc;
}