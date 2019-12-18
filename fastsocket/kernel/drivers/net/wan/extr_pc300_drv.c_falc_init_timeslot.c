#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tslot_bitmap; } ;
typedef  TYPE_1__ pc300chconf_t ;
struct TYPE_9__ {int /*<<< orphan*/  falc; int /*<<< orphan*/  conf; } ;
typedef  TYPE_2__ pc300ch_t ;
struct TYPE_10__ {int /*<<< orphan*/ * chan; } ;
typedef  TYPE_3__ pc300_t ;
struct TYPE_11__ {int num_channels; } ;
typedef  TYPE_4__ falc_t ;

/* Variables and functions */
 int /*<<< orphan*/  falc_close_timeslot (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  falc_open_timeslot (TYPE_3__*,int,int) ; 

__attribute__((used)) static void falc_init_timeslot(pc300_t * card, int ch)
{
	pc300ch_t *chan = (pc300ch_t *) & card->chan[ch];
	pc300chconf_t *conf = (pc300chconf_t *) & chan->conf;
	falc_t *pfalc = (falc_t *) & chan->falc;
	int tslot;

	for (tslot = 0; tslot < pfalc->num_channels; tslot++) {
		if (conf->tslot_bitmap & (1 << tslot)) {
			// Channel enabled
			falc_open_timeslot(card, ch, tslot + 1);
		} else {
			// Channel disabled
			falc_close_timeslot(card, ch, tslot + 1);
		}
	}
}