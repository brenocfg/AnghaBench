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
struct bna_enet {TYPE_2__* bna; } ;
typedef  int /*<<< orphan*/  mac_t ;
struct TYPE_3__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_4__ {TYPE_1__ ioceth; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_nw_ioc_get_mac (int /*<<< orphan*/ *) ; 

void
bna_enet_perm_mac_get(struct bna_enet *enet, mac_t *mac)
{
	*mac = bfa_nw_ioc_get_mac(&enet->bna->ioceth.ioc);
}