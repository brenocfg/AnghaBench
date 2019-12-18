#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct brcms_info {int /*<<< orphan*/  mute_tx; TYPE_3__* wlc; TYPE_2__* pub; } ;
struct TYPE_6__ {TYPE_1__* hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; } ;
struct TYPE_4__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_init (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_reset (struct brcms_info*) ; 

void brcms_init(struct brcms_info *wl)
{
	brcms_dbg_info(wl->wlc->hw->d11core, "Initializing wl%d\n",
		       wl->pub->unit);
	brcms_reset(wl);
	brcms_c_init(wl->wlc, wl->mute_tx);
}