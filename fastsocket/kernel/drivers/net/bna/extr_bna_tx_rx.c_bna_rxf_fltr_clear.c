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
struct bna_rxf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_HARD_CLEANUP ; 
 scalar_t__ bna_rxf_allmulti_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 scalar_t__ bna_rxf_mcast_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 scalar_t__ bna_rxf_promisc_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 scalar_t__ bna_rxf_ucast_cfg_reset (struct bna_rxf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bna_rxf_fltr_clear(struct bna_rxf *rxf)
{
	if (bna_rxf_ucast_cfg_reset(rxf, BNA_HARD_CLEANUP))
		return 1;

	if (bna_rxf_mcast_cfg_reset(rxf, BNA_HARD_CLEANUP))
		return 1;

	if (bna_rxf_promisc_cfg_reset(rxf, BNA_HARD_CLEANUP))
		return 1;

	if (bna_rxf_allmulti_cfg_reset(rxf, BNA_HARD_CLEANUP))
		return 1;

	return 0;
}