#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fc_seq {int dummy; } ;
struct TYPE_5__ {scalar_t__ port_name; } ;
struct fc_rport_priv {scalar_t__ rp_state; unsigned int r_a_tov; struct fc_lport* local_port; int /*<<< orphan*/  kref; int /*<<< orphan*/  rp_mutex; TYPE_2__ ids; } ;
struct TYPE_6__ {int /*<<< orphan*/  rport_destroy; } ;
struct fc_lport {scalar_t__ wwpn; TYPE_3__ tt; } ;
struct fc_frame {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sp_r_a_tov; } ;
struct fc_els_flogi {TYPE_1__ fl_csp; } ;

/* Variables and functions */
 scalar_t__ ELS_LS_ACC ; 
 struct fc_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,...) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 scalar_t__ RPORT_ST_FLOGI ; 
 int /*<<< orphan*/  RPORT_ST_PLOGI_WAIT ; 
 int /*<<< orphan*/  fc_els_resp_type (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_flogi* fc_frame_payload_get (struct fc_frame*,int) ; 
 scalar_t__ fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_enter_plogi (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_error (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_error_retry (struct fc_rport_priv*,struct fc_frame*) ; 
 scalar_t__ fc_rport_login_complete (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_state_enter (struct fc_rport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_rport_flogi_resp(struct fc_seq *sp, struct fc_frame *fp,
				void *rp_arg)
{
	struct fc_rport_priv *rdata = rp_arg;
	struct fc_lport *lport = rdata->local_port;
	struct fc_els_flogi *flogi;
	unsigned int r_a_tov;

	FC_RPORT_DBG(rdata, "Received a FLOGI %s\n", fc_els_resp_type(fp));

	if (fp == ERR_PTR(-FC_EX_CLOSED))
		goto put;

	mutex_lock(&rdata->rp_mutex);

	if (rdata->rp_state != RPORT_ST_FLOGI) {
		FC_RPORT_DBG(rdata, "Received a FLOGI response, but in state "
			     "%s\n", fc_rport_state(rdata));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_rport_error(rdata, fp);
		goto err;
	}

	if (fc_frame_payload_op(fp) != ELS_LS_ACC)
		goto bad;
	if (fc_rport_login_complete(rdata, fp))
		goto bad;

	flogi = fc_frame_payload_get(fp, sizeof(*flogi));
	if (!flogi)
		goto bad;
	r_a_tov = ntohl(flogi->fl_csp.sp_r_a_tov);
	if (r_a_tov > rdata->r_a_tov)
		rdata->r_a_tov = r_a_tov;

	if (rdata->ids.port_name < lport->wwpn)
		fc_rport_enter_plogi(rdata);
	else
		fc_rport_state_enter(rdata, RPORT_ST_PLOGI_WAIT);
out:
	fc_frame_free(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, rdata->local_port->tt.rport_destroy);
	return;
bad:
	FC_RPORT_DBG(rdata, "Bad FLOGI response\n");
	fc_rport_error_retry(rdata, fp);
	goto out;
}