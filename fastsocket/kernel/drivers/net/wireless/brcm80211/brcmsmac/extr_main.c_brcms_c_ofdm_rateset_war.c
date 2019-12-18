#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct brcms_c_info {TYPE_1__* band; TYPE_5__* default_bss; TYPE_4__* bsscfg; } ;
struct TYPE_12__ {int /*<<< orphan*/ * rates; } ;
struct TYPE_11__ {TYPE_6__ rateset; } ;
struct TYPE_10__ {TYPE_3__* current_bss; scalar_t__ associated; } ;
struct TYPE_8__ {int /*<<< orphan*/ * rates; } ;
struct TYPE_9__ {TYPE_2__ rateset; } ;
struct TYPE_7__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlc_phy_ofdm_rateset_war (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcms_c_ofdm_rateset_war(struct brcms_c_info *wlc)
{
	u8 r;
	bool war = false;

	if (wlc->bsscfg->associated)
		r = wlc->bsscfg->current_bss->rateset.rates[0];
	else
		r = wlc->default_bss->rateset.rates[0];

	wlc_phy_ofdm_rateset_war(wlc->band->pi, war);
}