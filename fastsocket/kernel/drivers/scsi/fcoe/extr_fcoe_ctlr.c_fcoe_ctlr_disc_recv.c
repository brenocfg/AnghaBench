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
 int /*<<< orphan*/  ELS_EXPL_NONE ; 
 int /*<<< orphan*/  ELS_LS_RJT ; 
 int /*<<< orphan*/  ELS_RJT_UNSUP ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int /*<<< orphan*/  stub1 (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ; 

__attribute__((used)) static void fcoe_ctlr_disc_recv(struct fc_lport *lport, struct fc_frame *fp)
{
	struct fc_seq_els_data rjt_data;

	rjt_data.reason = ELS_RJT_UNSUP;
	rjt_data.explan = ELS_EXPL_NONE;
	lport->tt.seq_els_rsp_send(fp, ELS_LS_RJT, &rjt_data);
	fc_frame_free(fp);
}