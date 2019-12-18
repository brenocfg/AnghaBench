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
typedef  size_t uint ;
struct brcms_c_info {TYPE_5__* default_bss; TYPE_4__** bandstate; TYPE_2__* pub; TYPE_1__* stf; } ;
typedef  scalar_t__ s32 ;
struct TYPE_12__ {int /*<<< orphan*/  mcs; } ;
struct TYPE_11__ {TYPE_6__ rateset; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  mcs; } ;
struct TYPE_10__ {TYPE_3__ hw_rateset; } ;
struct TYPE_8__ {size_t _nbands; int /*<<< orphan*/  _n_enab; } ;
struct TYPE_7__ {scalar_t__ txstreams; } ;

/* Variables and functions */
 scalar_t__ AUTO ; 
 int /*<<< orphan*/  BRCMS_BSS_HT ; 
 int /*<<< orphan*/  GMODE_AUTO ; 
 int /*<<< orphan*/  MCSSET_LEN ; 
 int /*<<< orphan*/  SUPPORT_11N ; 
 int /*<<< orphan*/  SUPPORT_HT ; 
 scalar_t__ WL_11N_2x2 ; 
 scalar_t__ WL_11N_3x3 ; 
 int /*<<< orphan*/  brcms_c_rateset_mcs_build (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  brcms_c_set_gmode (struct brcms_c_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int brcms_c_set_nmode(struct brcms_c_info *wlc)
{
	uint i;
	s32 nmode = AUTO;

	if (wlc->stf->txstreams == WL_11N_3x3)
		nmode = WL_11N_3x3;
	else
		nmode = WL_11N_2x2;

	/* force GMODE_AUTO if NMODE is ON */
	brcms_c_set_gmode(wlc, GMODE_AUTO, true);
	if (nmode == WL_11N_3x3)
		wlc->pub->_n_enab = SUPPORT_HT;
	else
		wlc->pub->_n_enab = SUPPORT_11N;
	wlc->default_bss->flags |= BRCMS_BSS_HT;
	/* add the mcs rates to the default and hw ratesets */
	brcms_c_rateset_mcs_build(&wlc->default_bss->rateset,
			      wlc->stf->txstreams);
	for (i = 0; i < wlc->pub->_nbands; i++)
		memcpy(wlc->bandstate[i]->hw_rateset.mcs,
		       wlc->default_bss->rateset.mcs, MCSSET_LEN);

	return 0;
}