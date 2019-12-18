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
struct bna_pause_config {int dummy; } ;
struct bna_enet {void (* pause_cbfn ) (struct bnad*) ;struct bna_pause_config pause_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_E_PAUSE_CFG ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bna_enet*,int /*<<< orphan*/ ) ; 

void
bna_enet_pause_config(struct bna_enet *enet,
		      struct bna_pause_config *pause_config,
		      void (*cbfn)(struct bnad *))
{
	enet->pause_config = *pause_config;

	enet->pause_cbfn = cbfn;

	bfa_fsm_send_event(enet, ENET_E_PAUSE_CFG);
}