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
struct bna_enet {int mtu; void (* mtu_cbfn ) (struct bnad*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_E_MTU_CFG ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_enet*,int /*<<< orphan*/ ) ; 

void
bna_enet_mtu_set(struct bna_enet *enet, int mtu,
		 void (*cbfn)(struct bnad *))
{
	enet->mtu = mtu;

	enet->mtu_cbfn = cbfn;

	bfa_fsm_send_event(enet, ENET_E_MTU_CFG);
}