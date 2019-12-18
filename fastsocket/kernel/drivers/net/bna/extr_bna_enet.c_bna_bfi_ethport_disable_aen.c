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
struct bna_ethport {int /*<<< orphan*/  flags; } ;
struct bfi_msgq_mhdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_ETHPORT_F_PORT_ENABLED ; 
 int /*<<< orphan*/  ETHPORT_E_DOWN ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_ethport*,int /*<<< orphan*/ ) ; 
 int ethport_is_up (struct bna_ethport*) ; 

__attribute__((used)) static void
bna_bfi_ethport_disable_aen(struct bna_ethport *ethport,
				struct bfi_msgq_mhdr *msghdr)
{
	int ethport_up = ethport_is_up(ethport);

	ethport->flags &= ~BNA_ETHPORT_F_PORT_ENABLED;

	if (ethport_up)
		bfa_fsm_send_event(ethport, ETHPORT_E_DOWN);
}