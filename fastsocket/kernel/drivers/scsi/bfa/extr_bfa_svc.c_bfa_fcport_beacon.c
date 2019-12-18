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
struct bfa_fcport_s {void* beacon; void* link_e2e_beacon; } ;
typedef  void* bfa_boolean_t ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,void*) ; 

void
bfa_fcport_beacon(void *dev, bfa_boolean_t beacon,
		  bfa_boolean_t link_e2e_beacon)
{
	struct bfa_s *bfa = dev;
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, beacon);
	bfa_trc(bfa, link_e2e_beacon);
	bfa_trc(bfa, fcport->beacon);
	bfa_trc(bfa, fcport->link_e2e_beacon);

	fcport->beacon = beacon;
	fcport->link_e2e_beacon = link_e2e_beacon;
}