#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; scalar_t__ egout; scalar_t__ pgout; scalar_t__ volume; scalar_t__ block; scalar_t__ fnum; scalar_t__ sustine; scalar_t__ tll; scalar_t__ rks; scalar_t__ eg_dphase; int /*<<< orphan*/  eg_phase; int /*<<< orphan*/  eg_mode; scalar_t__ feedback; scalar_t__* output; scalar_t__ dphase; scalar_t__ phase; int /*<<< orphan*/  sintbl; } ;
typedef  TYPE_1__ OPLL_SLOT ;

/* Variables and functions */
 int /*<<< orphan*/  EG_DP_WIDTH ; 
 int /*<<< orphan*/  SETTLE ; 
 int /*<<< orphan*/ * waveform ; 

__attribute__((used)) static void OPLL_SLOT_reset(OPLL_SLOT * slot, int type) {
	slot->type = type;
	slot->sintbl = waveform[0];
	slot->phase = 0;
	slot->dphase = 0;
	slot->output[0] = 0;
	slot->output[1] = 0;
	slot->feedback = 0;
	slot->eg_mode = SETTLE;
	slot->eg_phase = EG_DP_WIDTH;
	slot->eg_dphase = 0;
	slot->rks = 0;
	slot->tll = 0;
	slot->sustine = 0;
	slot->fnum = 0;
	slot->block = 0;
	slot->volume = 0;
	slot->pgout = 0;
	slot->egout = 0;
}