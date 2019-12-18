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
struct TYPE_2__ {int /*<<< orphan*/  (* elsct_send ) (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_lport*,int) ;} ;
struct fc_lport {int r_a_tov; TYPE_1__ tt; } ;
struct fc_frame {int dummy; } ;
struct fc_els_scr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_SCR ; 
 int /*<<< orphan*/  FC_FID_FCTRL ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPORT_ST_SCR ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_lport_error (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_scr_resp ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_state_enter (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_lport*,int) ; 

__attribute__((used)) static void fc_lport_enter_scr(struct fc_lport *lport)
{
	struct fc_frame *fp;

	FC_LPORT_DBG(lport, "Entered SCR state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_SCR);

	fp = fc_frame_alloc(lport, sizeof(struct fc_els_scr));
	if (!fp) {
		fc_lport_error(lport, fp);
		return;
	}

	if (!lport->tt.elsct_send(lport, FC_FID_FCTRL, fp, ELS_SCR,
				  fc_lport_scr_resp, lport,
				  2 * lport->r_a_tov))
		fc_lport_error(lport, NULL);
}