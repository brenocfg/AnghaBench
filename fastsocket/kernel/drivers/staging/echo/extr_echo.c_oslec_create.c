#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct oslec_state {int taps; int curr_pos; int cng_level; int Lbgn_upper; int Lbgn_upper_acc; struct oslec_state** fir_taps16; scalar_t__ Lbgn_acc; scalar_t__ Lbgn; scalar_t__ rx_2; scalar_t__ rx_1; scalar_t__ tx_2; scalar_t__ tx_1; scalar_t__ Lclean_bg; scalar_t__ Lclean; scalar_t__ Lrx; scalar_t__ Ltx; scalar_t__ Lclean_bgacc; scalar_t__ Lcleanacc; scalar_t__ Lrxacc; scalar_t__ Ltxacc; scalar_t__ Pstates; scalar_t__ cond_met; void* snapshot; scalar_t__* yvrx; scalar_t__* xvrx; scalar_t__* yvtx; scalar_t__* xvtx; int /*<<< orphan*/  fir_state_bg; int /*<<< orphan*/  fir_state; int /*<<< orphan*/  log2taps; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  fir16_create (int /*<<< orphan*/ *,struct oslec_state*,int) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct oslec_state*) ; 
 struct oslec_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oslec_adaption_mode (struct oslec_state*,int) ; 
 int /*<<< orphan*/  top_bit (int) ; 

struct oslec_state *oslec_create(int len, int adaption_mode)
{
	struct oslec_state *ec;
	int i;

	ec = kzalloc(sizeof(*ec), GFP_KERNEL);
	if (!ec)
		return NULL;

	ec->taps = len;
	ec->log2taps = top_bit(len);
	ec->curr_pos = ec->taps - 1;

	for (i = 0; i < 2; i++) {
		ec->fir_taps16[i] =
		    kcalloc(ec->taps, sizeof(int16_t), GFP_KERNEL);
		if (!ec->fir_taps16[i])
			goto error_oom;
	}

	fir16_create(&ec->fir_state, ec->fir_taps16[0], ec->taps);
	fir16_create(&ec->fir_state_bg, ec->fir_taps16[1], ec->taps);

	for (i = 0; i < 5; i++)
		ec->xvtx[i] = ec->yvtx[i] = ec->xvrx[i] = ec->yvrx[i] = 0;

	ec->cng_level = 1000;
	oslec_adaption_mode(ec, adaption_mode);

	ec->snapshot = kcalloc(ec->taps, sizeof(int16_t), GFP_KERNEL);
	if (!ec->snapshot)
		goto error_oom;

	ec->cond_met = 0;
	ec->Pstates = 0;
	ec->Ltxacc = ec->Lrxacc = ec->Lcleanacc = ec->Lclean_bgacc = 0;
	ec->Ltx = ec->Lrx = ec->Lclean = ec->Lclean_bg = 0;
	ec->tx_1 = ec->tx_2 = ec->rx_1 = ec->rx_2 = 0;
	ec->Lbgn = ec->Lbgn_acc = 0;
	ec->Lbgn_upper = 200;
	ec->Lbgn_upper_acc = ec->Lbgn_upper << 13;

	return ec;

error_oom:
	for (i = 0; i < 2; i++)
		kfree(ec->fir_taps16[i]);

	kfree(ec);
	return NULL;
}