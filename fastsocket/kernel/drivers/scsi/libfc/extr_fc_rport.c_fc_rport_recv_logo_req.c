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
typedef  int /*<<< orphan*/  u32 ;
struct fc_rport_priv {int /*<<< orphan*/  rp_mutex; } ;
struct TYPE_3__ {int /*<<< orphan*/  disc_mutex; } ;
struct TYPE_4__ {struct fc_rport_priv* (* rport_lookup ) (struct fc_lport*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* seq_els_rsp_send ) (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct fc_lport {TYPE_1__ disc; TYPE_2__ tt; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_RPORT_ID_DBG (struct fc_lport*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RPORT_EV_LOGO ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_sid (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_enter_delete (struct fc_rport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fc_rport_priv* stub2 (struct fc_lport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_rport_recv_logo_req(struct fc_lport *lport, struct fc_frame *fp)
{
	struct fc_rport_priv *rdata;
	u32 sid;

	lport->tt.seq_els_rsp_send(fp, ELS_LS_ACC, NULL);

	sid = fc_frame_sid(fp);

	mutex_lock(&lport->disc.disc_mutex);
	rdata = lport->tt.rport_lookup(lport, sid);
	if (rdata) {
		mutex_lock(&rdata->rp_mutex);
		FC_RPORT_DBG(rdata, "Received LOGO request while in state %s\n",
			     fc_rport_state(rdata));

		fc_rport_enter_delete(rdata, RPORT_EV_LOGO);
		mutex_unlock(&rdata->rp_mutex);
	} else
		FC_RPORT_ID_DBG(lport, sid,
				"Received LOGO from non-logged-in port\n");
	mutex_unlock(&lport->disc.disc_mutex);
	fc_frame_free(fp);
}