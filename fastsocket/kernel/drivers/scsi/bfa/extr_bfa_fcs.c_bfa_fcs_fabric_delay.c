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
struct bfa_fcs_fabric_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_FABRIC_SM_DELAYED ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_fabric_delay(void *cbarg)
{
	struct bfa_fcs_fabric_s *fabric = cbarg;

	bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_DELAYED);
}