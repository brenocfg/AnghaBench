#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_fcs_lport_ms_s {TYPE_2__* port; } ;
struct TYPE_3__ {int /*<<< orphan*/  ms_timeouts; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSSM_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_ms_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_ms_timeout(void *arg)
{
	struct bfa_fcs_lport_ms_s *ms = (struct bfa_fcs_lport_ms_s *) arg;

	ms->port->stats.ms_timeouts++;
	bfa_sm_send_event(ms, MSSM_EVENT_TIMEOUT);
}