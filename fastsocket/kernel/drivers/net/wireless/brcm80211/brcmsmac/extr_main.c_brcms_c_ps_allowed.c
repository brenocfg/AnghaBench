#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_info {int filter_flags; TYPE_1__* pub; struct brcms_bss_cfg* bsscfg; } ;
struct brcms_bss_cfg {int /*<<< orphan*/  BSS; scalar_t__ associated; } ;
struct TYPE_2__ {int /*<<< orphan*/  associated; } ;

/* Variables and functions */
 int FIF_PROMISC_IN_BSS ; 

__attribute__((used)) static bool brcms_c_ps_allowed(struct brcms_c_info *wlc)
{
	struct brcms_bss_cfg *cfg = wlc->bsscfg;

	/* disallow PS when one of the following global conditions meets */
	if (!wlc->pub->associated)
		return false;

	/* disallow PS when one of these meets when not scanning */
	if (wlc->filter_flags & FIF_PROMISC_IN_BSS)
		return false;

	if (cfg->associated) {
		/*
		 * disallow PS when one of the following
		 * bsscfg specific conditions meets
		 */
		if (!cfg->BSS)
			return false;

		return false;
	}

	return true;
}