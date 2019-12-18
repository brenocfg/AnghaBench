#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int pll_time; scalar_t__ dcd_time; int dcd_sum0; scalar_t__ dcd_sum1; scalar_t__ dcd_sum2; unsigned char last_rxbit; } ;
struct TYPE_6__ {int shreg; TYPE_2__ ser12; } ;
struct TYPE_4__ {int cur_pllcorr; } ;
struct baycom_state {int baud_us; TYPE_3__ modem; TYPE_1__ debug_vals; int /*<<< orphan*/  hdrv; int /*<<< orphan*/  opt_dcd; } ;

/* Variables and functions */
 int abs (int) ; 
 int /*<<< orphan*/  hdlcdrv_putbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hdlcdrv_setdcd (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline__ void ser12_rx(struct net_device *dev, struct baycom_state *bc, struct timeval *tv, unsigned char curs)
{
	int timediff;
	int bdus8 = bc->baud_us >> 3;
	int bdus4 = bc->baud_us >> 2;
	int bdus2 = bc->baud_us >> 1;

	timediff = 1000000 + tv->tv_usec - bc->modem.ser12.pll_time;
	while (timediff >= 500000)
		timediff -= 1000000;
	while (timediff >= bdus2) {
		timediff -= bc->baud_us;
		bc->modem.ser12.pll_time += bc->baud_us;
		bc->modem.ser12.dcd_time--;
		/* first check if there is room to add a bit */
		if (bc->modem.shreg & 1) {
			hdlcdrv_putbits(&bc->hdrv, (bc->modem.shreg >> 1) ^ 0xffff);
			bc->modem.shreg = 0x10000;
		}
		/* add a one bit */
		bc->modem.shreg >>= 1;
	}
	if (bc->modem.ser12.dcd_time <= 0) {
		if (!bc->opt_dcd)
			hdlcdrv_setdcd(&bc->hdrv, (bc->modem.ser12.dcd_sum0 + 
						   bc->modem.ser12.dcd_sum1 + 
						   bc->modem.ser12.dcd_sum2) < 0);
		bc->modem.ser12.dcd_sum2 = bc->modem.ser12.dcd_sum1;
		bc->modem.ser12.dcd_sum1 = bc->modem.ser12.dcd_sum0;
		bc->modem.ser12.dcd_sum0 = 2; /* slight bias */
		bc->modem.ser12.dcd_time += 120;
	}
	if (bc->modem.ser12.last_rxbit != curs) {
		bc->modem.ser12.last_rxbit = curs;
		bc->modem.shreg |= 0x10000;
		/* adjust the PLL */
		if (timediff > 0)
			bc->modem.ser12.pll_time += bdus8;
		else
			bc->modem.ser12.pll_time += 1000000 - bdus8;
		/* update DCD */
		if (abs(timediff) > bdus4)
			bc->modem.ser12.dcd_sum0 += 4;
		else
			bc->modem.ser12.dcd_sum0--;
#ifdef BAYCOM_DEBUG
		bc->debug_vals.cur_pllcorr = timediff;
#endif /* BAYCOM_DEBUG */
	}
	while (bc->modem.ser12.pll_time >= 1000000)
		bc->modem.ser12.pll_time -= 1000000;
}