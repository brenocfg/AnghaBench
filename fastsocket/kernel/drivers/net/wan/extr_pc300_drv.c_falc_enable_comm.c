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
struct TYPE_9__ {int /*<<< orphan*/  falc; } ;
typedef  TYPE_2__ pc300ch_t ;
struct TYPE_8__ {scalar_t__ cpld_reg1; scalar_t__ falcbase; } ;
struct TYPE_10__ {TYPE_1__ hw; int /*<<< orphan*/ * chan; } ;
typedef  TYPE_3__ pc300_t ;
struct TYPE_11__ {scalar_t__ full_bandwidth; } ;
typedef  TYPE_4__ falc_t ;

/* Variables and functions */
 int CPLD_REG1_FALC_CTS ; 
 int CPLD_REG1_FALC_DCD ; 
 int cpc_readb (scalar_t__) ; 
 int /*<<< orphan*/  cpc_writeb (scalar_t__,int) ; 
 int /*<<< orphan*/  falc_init_timeslot (TYPE_3__*,int) ; 
 int /*<<< orphan*/  falc_open_all_timeslots (TYPE_3__*,int) ; 

__attribute__((used)) static void falc_enable_comm(pc300_t * card, int ch)
{
	pc300ch_t *chan = (pc300ch_t *) & card->chan[ch];
	falc_t *pfalc = (falc_t *) & chan->falc;

	if (pfalc->full_bandwidth) {
		falc_open_all_timeslots(card, ch);
	} else {
		falc_init_timeslot(card, ch);
	}
	// CTS/DCD ON
	cpc_writeb(card->hw.falcbase + card->hw.cpld_reg1,
		   cpc_readb(card->hw.falcbase + card->hw.cpld_reg1) &
		   ~((CPLD_REG1_FALC_DCD | CPLD_REG1_FALC_CTS) << (2 * ch)));
}