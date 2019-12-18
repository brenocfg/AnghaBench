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
struct bna_ethport {TYPE_2__* bna; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ enet; } ;

/* Variables and functions */
 scalar_t__ BNA_ENET_T_REGULAR ; 
 int /*<<< orphan*/  bna_bfi_ethport_admin_up (struct bna_ethport*) ; 
 int /*<<< orphan*/  bna_bfi_ethport_lpbk_up (struct bna_ethport*) ; 

__attribute__((used)) static void
bna_bfi_ethport_up(struct bna_ethport *ethport)
{
	if (ethport->bna->enet.type == BNA_ENET_T_REGULAR)
		bna_bfi_ethport_admin_up(ethport);
	else
		bna_bfi_ethport_lpbk_up(ethport);
}