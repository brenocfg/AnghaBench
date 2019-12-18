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
struct TYPE_2__ {int curr_pos; } ;
struct oslec_state {int Lbgn_upper; int Lbgn_upper_acc; int taps; int curr_pos; scalar_t__ Pstates; int /*<<< orphan*/ * fir_taps16; TYPE_1__ fir_state_bg; TYPE_1__ fir_state; scalar_t__ nonupdate_dwell; scalar_t__ Lbgn_acc; scalar_t__ Lbgn; scalar_t__ rx_2; scalar_t__ rx_1; scalar_t__ tx_2; scalar_t__ tx_1; scalar_t__ Lclean_bg; scalar_t__ Lclean; scalar_t__ Lrx; scalar_t__ Ltx; scalar_t__ Lclean_bgacc; scalar_t__ Lcleanacc; scalar_t__ Lrxacc; scalar_t__ Ltxacc; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  fir16_flush (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void oslec_flush(struct oslec_state *ec)
{
	int i;

	ec->Ltxacc = ec->Lrxacc = ec->Lcleanacc = ec->Lclean_bgacc = 0;
	ec->Ltx = ec->Lrx = ec->Lclean = ec->Lclean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->rx_1 = ec->rx_2 = 0;

	ec->Lbgn = ec->Lbgn_acc = 0;
	ec->Lbgn_upper = 200;
	ec->Lbgn_upper_acc = ec->Lbgn_upper << 13;

	ec->nonupdate_dwell = 0;

	fir16_flush(&ec->fir_state);
	fir16_flush(&ec->fir_state_bg);
	ec->fir_state.curr_pos = ec->taps - 1;
	ec->fir_state_bg.curr_pos = ec->taps - 1;
	for (i = 0; i < 2; i++)
		memset(ec->fir_taps16[i], 0, ec->taps * sizeof(int16_t));

	ec->curr_pos = ec->taps - 1;
	ec->Pstates = 0;
}