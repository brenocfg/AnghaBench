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
typedef  int /*<<< orphan*/  u8 ;
struct brcms_c_info {TYPE_3__* stf; TYPE_2__* pub; TYPE_1__* hw; } ;
typedef  scalar_t__ s8 ;
struct TYPE_6__ {int /*<<< orphan*/  txchain; scalar_t__ spatial_policy; } ;
struct TYPE_5__ {int /*<<< orphan*/  unit; } ;
struct TYPE_4__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int MAX_SPATIAL_EXPANSION ; 
 int MAX_STREAMS_SUPPORTED ; 
 int /*<<< orphan*/  brcms_c_stf_txcore_set (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_dbg_ht (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * txcore_default ; 

__attribute__((used)) static int brcms_c_stf_spatial_policy_set(struct brcms_c_info *wlc, int val)
{
	int i;
	u8 core_mask = 0;

	brcms_dbg_ht(wlc->hw->d11core, "wl%d: val %x\n", wlc->pub->unit,
		     val);

	wlc->stf->spatial_policy = (s8) val;
	for (i = 1; i <= MAX_STREAMS_SUPPORTED; i++) {
		core_mask = (val == MAX_SPATIAL_EXPANSION) ?
		    wlc->stf->txchain : txcore_default[i];
		brcms_c_stf_txcore_set(wlc, (u8) i, core_mask);
	}
	return 0;
}