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
struct bfad_s {int bfad_flags; } ;

/* Variables and functions */
 int BFAD_PORT_ONLINE ; 
 int BFAD_RPORT_ONLINE ; 
 int HZ ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int bfa_linkup_delay ; 
 int /*<<< orphan*/  schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

void
bfad_rport_online_wait(struct bfad_s *bfad)
{
	int i;
	int rport_delay = 10;

	for (i = 0; !(bfad->bfad_flags & BFAD_PORT_ONLINE)
		&& i < bfa_linkup_delay; i++) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(HZ);
	}

	if (bfad->bfad_flags & BFAD_PORT_ONLINE) {
		rport_delay = rport_delay < bfa_linkup_delay ?
			rport_delay : bfa_linkup_delay;
		for (i = 0; !(bfad->bfad_flags & BFAD_RPORT_ONLINE)
			&& i < rport_delay; i++) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_timeout(HZ);
		}

		if (rport_delay > 0 && (bfad->bfad_flags & BFAD_RPORT_ONLINE)) {
			set_current_state(TASK_UNINTERRUPTIBLE);
			schedule_timeout(rport_delay * HZ);
		}
	}
}