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
struct bfa_fcport_s {int dummy; } ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  BFA_FCPORT_SM_HWFAIL ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trunk_iocdisable (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_fcport_iocdisable(struct bfa_s *bfa)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_sm_send_event(fcport, BFA_FCPORT_SM_HWFAIL);
	bfa_trunk_iocdisable(bfa);
}