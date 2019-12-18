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
struct TYPE_2__ {int /*<<< orphan*/  reset_stats_cbarg; int /*<<< orphan*/  (* reset_stats_cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct bfa_cee_s {TYPE_1__ cbfn; int /*<<< orphan*/  reset_stats_pending; int /*<<< orphan*/  reset_stats_status; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_cee_reset_stats_isr(struct bfa_cee_s *cee, bfa_status_t status)
{
	cee->reset_stats_status = status;
	cee->reset_stats_pending = BFA_FALSE;
	if (cee->cbfn.reset_stats_cbfn)
		cee->cbfn.reset_stats_cbfn(cee->cbfn.reset_stats_cbarg, status);
}