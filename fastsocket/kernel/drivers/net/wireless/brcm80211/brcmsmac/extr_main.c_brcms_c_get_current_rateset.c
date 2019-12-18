#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_rateset {int /*<<< orphan*/  count; int /*<<< orphan*/  rates; } ;
struct brcms_c_info {TYPE_4__* default_bss; TYPE_3__* bsscfg; TYPE_1__* pub; } ;
struct brcm_rateset {int /*<<< orphan*/  rates; int /*<<< orphan*/  count; } ;
struct TYPE_8__ {struct brcms_c_rateset rateset; } ;
struct TYPE_7__ {TYPE_2__* current_bss; } ;
struct TYPE_6__ {struct brcms_c_rateset rateset; } ;
struct TYPE_5__ {scalar_t__ associated; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void brcms_c_get_current_rateset(struct brcms_c_info *wlc,
				 struct brcm_rateset *currs)
{
	struct brcms_c_rateset *rs;

	if (wlc->pub->associated)
		rs = &wlc->bsscfg->current_bss->rateset;
	else
		rs = &wlc->default_bss->rateset;

	/* Copy only legacy rateset section */
	currs->count = rs->count;
	memcpy(&currs->rates, &rs->rates, rs->count);
}