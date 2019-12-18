#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort ;
struct TYPE_7__ {TYPE_1__* state; } ;
typedef  TYPE_2__ ser_info_t ;
struct TYPE_8__ {int cp_cr; } ;
struct TYPE_6__ {int smc_scc_num; } ;
typedef  TYPE_3__ QUICC ;

/* Variables and functions */
 int CPM_CR_FLG ; 
 int /*<<< orphan*/  CPM_CR_RESTART_TX ; 
 int NUM_IS_SCC ; 
 int PORT_NUM (int) ; 
 int mk_cr_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* pquicc ; 
 int /*<<< orphan*/ * scc_chan_map ; 
 int /*<<< orphan*/ * smc_chan_map ; 

__attribute__((used)) static void end_break(ser_info_t *info)
{
	volatile QUICC *cp;
	ushort	chan;
	int idx;

	cp = pquicc;

	idx = PORT_NUM(info->state->smc_scc_num);
	if (info->state->smc_scc_num & NUM_IS_SCC)
		chan = scc_chan_map[idx];
	else
		chan = smc_chan_map[idx];

	cp->cp_cr = mk_cr_cmd(chan, CPM_CR_RESTART_TX) | CPM_CR_FLG;
	while (cp->cp_cr & CPM_CR_FLG);
}