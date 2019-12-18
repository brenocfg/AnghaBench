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
struct TYPE_2__ {int /*<<< orphan*/  (* exch_done ) (int /*<<< orphan*/ *) ;} ;
struct fc_lport {TYPE_1__ tt; } ;
struct fc_fcp_pkt {int status_code; int /*<<< orphan*/ * seq_ptr; struct fc_lport* lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_fcp_cleanup_cmd(struct fc_fcp_pkt *fsp, int error)
{
	struct fc_lport *lport = fsp->lp;

	if (fsp->seq_ptr) {
		lport->tt.exch_done(fsp->seq_ptr);
		fsp->seq_ptr = NULL;
	}
	fsp->status_code = error;
}