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
struct fc_rport_priv {scalar_t__ rp_state; int /*<<< orphan*/  rp_mutex; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*) ; 
 int /*<<< orphan*/  FC_RP_STARTED ; 
 int /*<<< orphan*/  RPORT_EV_STOP ; 
 scalar_t__ RPORT_ST_DELETE ; 
 int /*<<< orphan*/  fc_rport_enter_delete (struct fc_rport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_enter_logo (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fc_rport_logoff(struct fc_rport_priv *rdata)
{
	mutex_lock(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Remove port\n");

	rdata->flags &= ~FC_RP_STARTED;
	if (rdata->rp_state == RPORT_ST_DELETE) {
		FC_RPORT_DBG(rdata, "Port in Delete state, not removing\n");
		goto out;
	}
	fc_rport_enter_logo(rdata);

	/*
	 * Change the state to Delete so that we discard
	 * the response.
	 */
	fc_rport_enter_delete(rdata, RPORT_EV_STOP);
out:
	mutex_unlock(&rdata->rp_mutex);
	return 0;
}