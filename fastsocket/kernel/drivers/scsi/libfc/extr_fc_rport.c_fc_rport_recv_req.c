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
struct fc_seq_els_data {int /*<<< orphan*/  explan; int /*<<< orphan*/  reason; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* seq_els_rsp_send ) (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
#define  ELS_ADISC 136 
 int /*<<< orphan*/  ELS_EXPL_NONE ; 
#define  ELS_FLOGI 135 
#define  ELS_LOGO 134 
 int /*<<< orphan*/  ELS_LS_RJT ; 
#define  ELS_PLOGI 133 
#define  ELS_PRLI 132 
#define  ELS_PRLO 131 
#define  ELS_REC 130 
 int /*<<< orphan*/  ELS_RJT_UNSUP ; 
#define  ELS_RLS 129 
#define  ELS_RRQ 128 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_els_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_flogi_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_logo_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_plogi_req (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  stub1 (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ; 

__attribute__((used)) static void fc_rport_recv_req(struct fc_lport *lport, struct fc_frame *fp)
{
	struct fc_seq_els_data els_data;

	/*
	 * Handle FLOGI, PLOGI and LOGO requests separately, since they
	 * don't require prior login.
	 * Check for unsupported opcodes first and reject them.
	 * For some ops, it would be incorrect to reject with "PLOGI required".
	 */
	switch (fc_frame_payload_op(fp)) {
	case ELS_FLOGI:
		fc_rport_recv_flogi_req(lport, fp);
		break;
	case ELS_PLOGI:
		fc_rport_recv_plogi_req(lport, fp);
		break;
	case ELS_LOGO:
		fc_rport_recv_logo_req(lport, fp);
		break;
	case ELS_PRLI:
	case ELS_PRLO:
	case ELS_ADISC:
	case ELS_RRQ:
	case ELS_REC:
	case ELS_RLS:
		fc_rport_recv_els_req(lport, fp);
		break;
	default:
		els_data.reason = ELS_RJT_UNSUP;
		els_data.explan = ELS_EXPL_NONE;
		lport->tt.seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
		fc_frame_free(fp);
		break;
	}
}