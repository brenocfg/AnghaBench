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
struct hfc_multi {TYPE_1__* chan; } ;
struct TYPE_2__ {int conf; int /*<<< orphan*/  bank_rx; int /*<<< orphan*/  slot_rx; int /*<<< orphan*/  bank_tx; int /*<<< orphan*/  slot_tx; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  mode_hfcmulti (struct hfc_multi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hfcmulti_conf(struct hfc_multi *hc, int ch, int num)
{
	if (num >= 0 && num <= 7)
		hc->chan[ch].conf = num;
	else
		hc->chan[ch].conf = -1;
	mode_hfcmulti(hc, ch, hc->chan[ch].protocol, hc->chan[ch].slot_tx,
	    hc->chan[ch].bank_tx, hc->chan[ch].slot_rx,
	    hc->chan[ch].bank_rx);
}