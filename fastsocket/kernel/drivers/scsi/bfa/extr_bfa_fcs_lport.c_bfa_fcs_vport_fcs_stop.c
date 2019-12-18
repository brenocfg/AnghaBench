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
struct bfa_fcs_vport_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_VPORT_SM_STOP ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_vport_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcs_vport_fcs_stop(struct bfa_fcs_vport_s *vport)
{
	bfa_sm_send_event(vport, BFA_FCS_VPORT_SM_STOP);
}