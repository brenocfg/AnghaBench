#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct fc_seq {int dummy; } ;
struct TYPE_5__ {void* node_name; void* port_name; } ;
struct fc_rport_priv {scalar_t__ rp_state; struct fc_lport* local_port; int /*<<< orphan*/  kref; int /*<<< orphan*/  rp_mutex; int /*<<< orphan*/  maxframe_size; scalar_t__ max_seq; void* sp_features; TYPE_1__ ids; } ;
struct TYPE_8__ {int /*<<< orphan*/  rport_destroy; } ;
struct fc_lport {TYPE_4__ tt; int /*<<< orphan*/  mfs; scalar_t__ point_to_multipoint; } ;
struct fc_frame {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sp_tot_seq; int /*<<< orphan*/  sp_features; } ;
struct fc_els_flogi {TYPE_3__* fl_cssp; TYPE_2__ fl_csp; int /*<<< orphan*/  fl_wwnn; int /*<<< orphan*/  fl_wwpn; } ;
struct TYPE_7__ {int /*<<< orphan*/  cp_con_seq; } ;

/* Variables and functions */
 scalar_t__ ELS_LS_ACC ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 scalar_t__ RPORT_ST_PLOGI ; 
 int /*<<< orphan*/  fc_els_resp_type (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_flogi* fc_frame_payload_get (struct fc_frame*,int) ; 
 scalar_t__ fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_plogi_get_maxframe (struct fc_els_flogi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_enter_prli (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_error_retry (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_login_complete (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 void* get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_rport_plogi_resp(struct fc_seq *sp, struct fc_frame *fp,
				void *rdata_arg)
{
	struct fc_rport_priv *rdata = rdata_arg;
	struct fc_lport *lport = rdata->local_port;
	struct fc_els_flogi *plp = NULL;
	u16 csp_seq;
	u16 cssp_seq;
	u8 op;

	mutex_lock(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Received a PLOGI %s\n", fc_els_resp_type(fp));

	if (rdata->rp_state != RPORT_ST_PLOGI) {
		FC_RPORT_DBG(rdata, "Received a PLOGI response, but in state "
			     "%s\n", fc_rport_state(rdata));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_rport_error_retry(rdata, fp);
		goto err;
	}

	op = fc_frame_payload_op(fp);
	if (op == ELS_LS_ACC &&
	    (plp = fc_frame_payload_get(fp, sizeof(*plp))) != NULL) {
		rdata->ids.port_name = get_unaligned_be64(&plp->fl_wwpn);
		rdata->ids.node_name = get_unaligned_be64(&plp->fl_wwnn);

		/* save plogi response sp_features for further reference */
		rdata->sp_features = ntohs(plp->fl_csp.sp_features);

		if (lport->point_to_multipoint)
			fc_rport_login_complete(rdata, fp);
		csp_seq = ntohs(plp->fl_csp.sp_tot_seq);
		cssp_seq = ntohs(plp->fl_cssp[3 - 1].cp_con_seq);
		if (cssp_seq < csp_seq)
			csp_seq = cssp_seq;
		rdata->max_seq = csp_seq;
		rdata->maxframe_size = fc_plogi_get_maxframe(plp, lport->mfs);
		fc_rport_enter_prli(rdata);
	} else
		fc_rport_error_retry(rdata, fp);

out:
	fc_frame_free(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
	kref_put(&rdata->kref, rdata->local_port->tt.rport_destroy);
}