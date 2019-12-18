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
struct corgi_ts {TYPE_1__* machinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wait_hsync ) () ;} ;

/* Variables and functions */
 unsigned int ADSCTRL_ADR_SH ; 
 unsigned int ADSCTRL_PD0 ; 
 unsigned int ADSCTRL_PD1 ; 
 unsigned int ADSCTRL_STS ; 
 int /*<<< orphan*/  CCNT (unsigned long) ; 
 int /*<<< orphan*/  PMNC_GET (unsigned long) ; 
 int /*<<< orphan*/  PMNC_SET (unsigned long) ; 
 int corgi_ssp_ads7846_get () ; 
 int /*<<< orphan*/  corgi_ssp_ads7846_put (int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int sync_receive_data_send_cmd(struct corgi_ts *corgi_ts, int doRecive, int doSend,
		unsigned int address, unsigned long wait_time)
{
	unsigned long timer1 = 0, timer2, pmnc = 0;
	int pos = 0;

	if (wait_time && doSend) {
		PMNC_GET(pmnc);
		if (!(pmnc & 0x01))
			PMNC_SET(0x01);

		/* polling HSync */
		corgi_ts->machinfo->wait_hsync();
		/* get CCNT */
		CCNT(timer1);
	}

	if (doRecive)
		pos = corgi_ssp_ads7846_get();

	if (doSend) {
		int cmd = ADSCTRL_PD0 | ADSCTRL_PD1 | (address << ADSCTRL_ADR_SH) | ADSCTRL_STS;
		/* dummy command */
		corgi_ssp_ads7846_put(cmd);
		corgi_ssp_ads7846_get();

		if (wait_time) {
			/* Wait after HSync */
			CCNT(timer2);
			if (timer2-timer1 > wait_time) {
				/* too slow - timeout, try again */
				corgi_ts->machinfo->wait_hsync();
				/* get CCNT */
				CCNT(timer1);
				/* Wait after HSync */
				CCNT(timer2);
			}
			while (timer2 - timer1 < wait_time)
				CCNT(timer2);
		}
		corgi_ssp_ads7846_put(cmd);
		if (wait_time && !(pmnc & 0x01))
			PMNC_SET(pmnc);
	}
	return pos;
}