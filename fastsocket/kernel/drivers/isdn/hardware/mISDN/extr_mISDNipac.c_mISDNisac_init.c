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
struct TYPE_4__ {int /*<<< orphan*/  send; } ;
struct TYPE_5__ {int Dprotocols; int nrbchan; TYPE_1__ D; } ;
struct TYPE_6__ {TYPE_2__ dev; void* hw; } ;
struct isac_hw {TYPE_3__ dch; int /*<<< orphan*/  open; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  release; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int ISDN_P_TE_S0 ; 
 int /*<<< orphan*/  MAX_DFRAME_LEN_L1 ; 
 int /*<<< orphan*/  isac_ctrl ; 
 int /*<<< orphan*/  isac_init ; 
 int /*<<< orphan*/  isac_l1hw ; 
 int /*<<< orphan*/  isac_ph_state_bh ; 
 int /*<<< orphan*/  isac_release ; 
 int /*<<< orphan*/  mISDN_initdchannel (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_dchannel ; 

int
mISDNisac_init(struct isac_hw *isac, void *hw)
{
	mISDN_initdchannel(&isac->dch, MAX_DFRAME_LEN_L1, isac_ph_state_bh);
	isac->dch.hw = hw;
	isac->dch.dev.D.send = isac_l1hw;
	isac->init = isac_init;
	isac->release = isac_release;
	isac->ctrl = isac_ctrl;
	isac->open = open_dchannel;
	isac->dch.dev.Dprotocols = (1 << ISDN_P_TE_S0);
	isac->dch.dev.nrbchan = 2;
	return 0;
}