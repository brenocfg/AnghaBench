#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* mdmreg; int /*<<< orphan*/  carrierwait; } ;
struct TYPE_9__ {scalar_t__ dialing; TYPE_1__ emu; } ;
typedef  TYPE_3__ modem_info ;
struct TYPE_8__ {TYPE_3__* info; } ;
struct TYPE_10__ {TYPE_2__ mdm; } ;

/* Variables and functions */
 int ISDN_MAX_CHANNELS ; 
 int /*<<< orphan*/  ISDN_TIMER_CARRIER ; 
 size_t REG_WAITC ; 
 int /*<<< orphan*/  RESULT_NO_CARRIER ; 
 TYPE_6__* dev ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_hup (TYPE_3__*,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,TYPE_3__*) ; 

void
isdn_tty_carrier_timeout(void)
{
	int ton = 0;
	int i;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
		modem_info *info = &dev->mdm.info[i];
		if (info->dialing) {
			if (info->emu.carrierwait++ > info->emu.mdmreg[REG_WAITC]) {
				info->dialing = 0;
				isdn_tty_modem_result(RESULT_NO_CARRIER, info);
				isdn_tty_modem_hup(info, 1);
			}
			else
				ton = 1;
		}
	}
	isdn_timer_ctrl(ISDN_TIMER_CARRIER, ton);
}