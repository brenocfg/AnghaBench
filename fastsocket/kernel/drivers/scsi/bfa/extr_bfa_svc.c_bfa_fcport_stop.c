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
struct bfa_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCPORT_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_STOP ; 
 int /*<<< orphan*/  bfa_sm_send_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trunk_iocdisable (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_fcport_stop(struct bfa_s *bfa)
{
	bfa_sm_send_event(BFA_FCPORT_MOD(bfa), BFA_FCPORT_SM_STOP);
	bfa_trunk_iocdisable(bfa);
}