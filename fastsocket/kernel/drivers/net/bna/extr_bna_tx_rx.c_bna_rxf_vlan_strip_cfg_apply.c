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
struct bna_rxf {int vlan_strip_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  bna_bfi_vlan_strip_enable (struct bna_rxf*) ; 

__attribute__((used)) static int
bna_rxf_vlan_strip_cfg_apply(struct bna_rxf *rxf)
{
	if (rxf->vlan_strip_pending) {
			rxf->vlan_strip_pending = false;
			bna_bfi_vlan_strip_enable(rxf);
			return 1;
	}

	return 0;
}