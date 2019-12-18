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
struct fc_rport_priv {int rp_state; int /*<<< orphan*/  rp_mutex; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*) ; 
 int /*<<< orphan*/  FC_RP_STARTED ; 
#define  RPORT_ST_DELETE 129 
#define  RPORT_ST_READY 128 
 int /*<<< orphan*/  fc_rport_enter_adisc (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_enter_flogi (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fc_rport_login(struct fc_rport_priv *rdata)
{
	mutex_lock(&rdata->rp_mutex);

	rdata->flags |= FC_RP_STARTED;
	switch (rdata->rp_state) {
	case RPORT_ST_READY:
		FC_RPORT_DBG(rdata, "ADISC port\n");
		fc_rport_enter_adisc(rdata);
		break;
	case RPORT_ST_DELETE:
		FC_RPORT_DBG(rdata, "Restart deleted port\n");
		break;
	default:
		FC_RPORT_DBG(rdata, "Login to port\n");
		fc_rport_enter_flogi(rdata);
		break;
	}
	mutex_unlock(&rdata->rp_mutex);

	return 0;
}