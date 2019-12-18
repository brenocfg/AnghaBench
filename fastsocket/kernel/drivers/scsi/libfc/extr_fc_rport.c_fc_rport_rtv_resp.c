#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct fc_seq {int dummy; } ;
struct fc_rport_priv {scalar_t__ rp_state; int r_a_tov; int e_d_tov; TYPE_2__* local_port; int /*<<< orphan*/  kref; int /*<<< orphan*/  rp_mutex; } ;
struct fc_frame {int dummy; } ;
struct fc_els_rtv_acc {int /*<<< orphan*/  rtv_e_d_tov; int /*<<< orphan*/  rtv_r_a_tov; int /*<<< orphan*/  rtv_toq; } ;
struct TYPE_3__ {int /*<<< orphan*/  rport_destroy; } ;
struct TYPE_4__ {TYPE_1__ tt; } ;

/* Variables and functions */
 scalar_t__ ELS_LS_ACC ; 
 int FC_ELS_RTV_EDRES ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 scalar_t__ RPORT_ST_RTV ; 
 int /*<<< orphan*/  fc_els_resp_type (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_rtv_acc* fc_frame_payload_get (struct fc_frame*,int) ; 
 scalar_t__ fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_enter_ready (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_error (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_rport_rtv_resp(struct fc_seq *sp, struct fc_frame *fp,
			      void *rdata_arg)
{
	struct fc_rport_priv *rdata = rdata_arg;
	u8 op;

	mutex_lock(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Received a RTV %s\n", fc_els_resp_type(fp));

	if (rdata->rp_state != RPORT_ST_RTV) {
		FC_RPORT_DBG(rdata, "Received a RTV response, but in state "
			     "%s\n", fc_rport_state(rdata));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_rport_error(rdata, fp);
		goto err;
	}

	op = fc_frame_payload_op(fp);
	if (op == ELS_LS_ACC) {
		struct fc_els_rtv_acc *rtv;
		u32 toq;
		u32 tov;

		rtv = fc_frame_payload_get(fp, sizeof(*rtv));
		if (rtv) {
			toq = ntohl(rtv->rtv_toq);
			tov = ntohl(rtv->rtv_r_a_tov);
			if (tov == 0)
				tov = 1;
			rdata->r_a_tov = tov;
			tov = ntohl(rtv->rtv_e_d_tov);
			if (toq & FC_ELS_RTV_EDRES)
				tov /= 1000000;
			if (tov == 0)
				tov = 1;
			rdata->e_d_tov = tov;
		}
	}

	fc_rport_enter_ready(rdata);

out:
	fc_frame_free(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
	kref_put(&rdata->kref, rdata->local_port->tt.rport_destroy);
}