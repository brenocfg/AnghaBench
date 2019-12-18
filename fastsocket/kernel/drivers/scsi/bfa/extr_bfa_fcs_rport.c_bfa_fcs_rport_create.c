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
typedef  int /*<<< orphan*/  u32 ;
struct bfa_fcs_rport_s {int dummy; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPSM_EVENT_PLOGI_SEND ; 
 int /*<<< orphan*/  WWN_NULL ; 
 struct bfa_fcs_rport_s* bfa_fcs_rport_alloc (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct bfa_fcs_rport_s *
bfa_fcs_rport_create(struct bfa_fcs_lport_s *port, u32 rpid)
{
	struct bfa_fcs_rport_s *rport;

	bfa_trc(port->fcs, rpid);
	rport = bfa_fcs_rport_alloc(port, WWN_NULL, rpid);
	if (!rport)
		return NULL;

	bfa_sm_send_event(rport, RPSM_EVENT_PLOGI_SEND);
	return rport;
}