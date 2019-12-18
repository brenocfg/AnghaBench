#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int msr; } ;
typedef  TYPE_2__ modem_info ;
struct TYPE_5__ {TYPE_2__* info; } ;
struct TYPE_7__ {TYPE_1__ mdm; } ;

/* Variables and functions */
 int ISDN_MAX_CHANNELS ; 
 int /*<<< orphan*/  ISDN_TIMER_MODEMRING ; 
 int /*<<< orphan*/  RESULT_RING ; 
 int UART_MSR_RI ; 
 TYPE_4__* dev ; 
 int /*<<< orphan*/  isdn_timer_ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isdn_tty_modem_result (int /*<<< orphan*/ ,TYPE_2__*) ; 

void
isdn_tty_modem_ring(void)
{
	int ton = 0;
	int i;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
		modem_info *info = &dev->mdm.info[i];
		if (info->msr & UART_MSR_RI) {
			ton = 1;
			isdn_tty_modem_result(RESULT_RING, info);
		}
	}
	isdn_timer_ctrl(ISDN_TIMER_MODEMRING, ton);
}