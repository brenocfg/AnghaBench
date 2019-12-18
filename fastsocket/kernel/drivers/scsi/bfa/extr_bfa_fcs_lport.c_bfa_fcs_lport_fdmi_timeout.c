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
struct bfa_fcs_lport_fdmi_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDMISM_EVENT_TIMEOUT ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_fdmi_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_fdmi_timeout(void *arg)
{
	struct bfa_fcs_lport_fdmi_s *fdmi = (struct bfa_fcs_lport_fdmi_s *) arg;

	bfa_sm_send_event(fdmi, FDMISM_EVENT_TIMEOUT);
}