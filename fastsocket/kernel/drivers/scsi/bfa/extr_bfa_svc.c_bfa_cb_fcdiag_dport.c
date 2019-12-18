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
struct bfa_dport_s {int /*<<< orphan*/ * cbarg; int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_cb_fcdiag_dport(struct bfa_dport_s *dport, bfa_status_t bfa_status)
{
	if (dport->cbfn != NULL) {
		dport->cbfn(dport->cbarg, bfa_status);
		dport->cbfn = NULL;
		dport->cbarg = NULL;
	}
}