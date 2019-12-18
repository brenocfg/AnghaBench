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
struct bfi_diag_ledtest_rsp_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct bfa_diag_s {TYPE_1__ ledtest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
diag_ledtest_comp(struct bfa_diag_s *diag, struct bfi_diag_ledtest_rsp_s *msg)
{
	bfa_trc(diag, diag->ledtest.lock);
	diag->ledtest.lock = BFA_FALSE;
	/* no bfa_cb_queue is needed because driver is not waiting */
}