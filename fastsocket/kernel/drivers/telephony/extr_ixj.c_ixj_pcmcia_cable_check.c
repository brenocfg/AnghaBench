#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_40__ {int lig; int lim; int iir; scalar_t__ him; scalar_t__ mcm; scalar_t__ mcg; } ;
struct TYPE_38__ {scalar_t__ hpd; scalar_t__ pll; scalar_t__ dl1; scalar_t__ dl2; scalar_t__ al; } ;
struct TYPE_39__ {int byte; TYPE_7__ bits; } ;
struct TYPE_36__ {int spd; scalar_t__ lpd; scalar_t__ hpd; scalar_t__ mpd; scalar_t__ cpd; } ;
struct TYPE_37__ {int byte; TYPE_5__ bits; } ;
struct TYPE_34__ {int rstc; int pwr; } ;
struct TYPE_35__ {int byte; TYPE_3__ bits; } ;
struct TYPE_32__ {scalar_t__ drf; scalar_t__ ed; } ;
struct TYPE_33__ {TYPE_1__ bits; void* byte; } ;
struct TYPE_30__ {int pcmciastate; int pcmciasct; int incheck; int pcmciascp; } ;
struct TYPE_26__ {int led2; int powerdown; scalar_t__ det; } ;
struct TYPE_29__ {int byte; TYPE_13__ bits; } ;
struct TYPE_27__ {int dev; int rw; int addr; } ;
struct TYPE_28__ {int byte; TYPE_14__ bits; } ;
struct TYPE_24__ {scalar_t__ sot; } ;
struct TYPE_25__ {int byte; TYPE_11__ bits; } ;
struct TYPE_23__ {int byte; TYPE_9__ bits; } ;
struct TYPE_31__ {int r_hook; TYPE_17__ flags; scalar_t__ XILINXbase; TYPE_16__ pslic; TYPE_15__ psccr; int /*<<< orphan*/  writers; int /*<<< orphan*/  readers; TYPE_12__ siaatt; TYPE_10__ sirxg; TYPE_8__ sic2; TYPE_6__ sic1; int /*<<< orphan*/  port; TYPE_4__ pccr2; TYPE_2__ pccr1; scalar_t__ checkwait; } ;
typedef  TYPE_18__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_POTS ; 
 int /*<<< orphan*/  PORT_SPEAKER ; 
 int hertz ; 
 void* inb_p (scalar_t__) ; 
 int inw_p (scalar_t__) ; 
 int /*<<< orphan*/  ixj_PCcontrol_wait (TYPE_18__*) ; 
 int /*<<< orphan*/  ixj_siadc (TYPE_18__*,int) ; 
 int /*<<< orphan*/  ixj_sidac (TYPE_18__*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  outw_p (int,scalar_t__) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ixj_pcmcia_cable_check(IXJ *j)
{
	j->pccr1.byte = inb_p(j->XILINXbase + 0x03);
	if (!j->flags.pcmciastate) {
		j->pccr2.byte = inb_p(j->XILINXbase + 0x02);
		if (j->pccr1.bits.drf || j->pccr2.bits.rstc) {
			j->flags.pcmciastate = 4;
			return 0;
		}
		if (j->pccr1.bits.ed) {
			j->pccr1.bits.ed = 0;
			j->psccr.bits.dev = 3;
			j->psccr.bits.rw = 1;
			outw_p(j->psccr.byte << 8, j->XILINXbase + 0x00);
			ixj_PCcontrol_wait(j);
			j->pslic.byte = inw_p(j->XILINXbase + 0x00) & 0xFF;
			j->pslic.bits.led2 = j->pslic.bits.det ? 1 : 0;
			j->psccr.bits.dev = 3;
			j->psccr.bits.rw = 0;
			outw_p(j->psccr.byte << 8 | j->pslic.byte, j->XILINXbase + 0x00);
			ixj_PCcontrol_wait(j);
			return j->pslic.bits.led2 ? 1 : 0;
		} else if (j->flags.pcmciasct) {
			return j->r_hook;
		} else {
			return 1;
		}
	} else if (j->flags.pcmciastate == 4) {
		if (!j->pccr1.bits.drf) {
			j->flags.pcmciastate = 3;
		}
		return 0;
	} else if (j->flags.pcmciastate == 3) {
		j->pccr2.bits.pwr = 0;
		j->pccr2.bits.rstc = 1;
		outb(j->pccr2.byte, j->XILINXbase + 0x02);
		j->checkwait = jiffies + (hertz * 2);
		j->flags.incheck = 1;
		j->flags.pcmciastate = 2;
		return 0;
	} else if (j->flags.pcmciastate == 2) {
		if (j->flags.incheck) {
			if (time_before(jiffies, j->checkwait)) {
				return 0;
			} else {
				j->flags.incheck = 0;
			}
		}
		j->pccr2.bits.pwr = 0;
		j->pccr2.bits.rstc = 0;
		outb_p(j->pccr2.byte, j->XILINXbase + 0x02);
		j->flags.pcmciastate = 1;
		return 0;
	} else if (j->flags.pcmciastate == 1) {
		j->flags.pcmciastate = 0;
		if (!j->pccr1.bits.drf) {
			j->psccr.bits.dev = 3;
			j->psccr.bits.rw = 1;
			outb_p(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);
			j->flags.pcmciascp = 1;		/* Set Cable Present Flag */

			j->flags.pcmciasct = (inw_p(j->XILINXbase + 0x00) >> 8) & 0x03;		/* Get Cable Type */

			if (j->flags.pcmciasct == 3) {
				j->flags.pcmciastate = 4;
				return 0;
			} else if (j->flags.pcmciasct == 0) {
				j->pccr2.bits.pwr = 1;
				j->pccr2.bits.rstc = 0;
				outb_p(j->pccr2.byte, j->XILINXbase + 0x02);
				j->port = PORT_SPEAKER;
			} else {
				j->port = PORT_POTS;
			}
			j->sic1.bits.cpd = 0;				/* Chip Power Down */
			j->sic1.bits.mpd = 0;				/* MIC Bias Power Down */
			j->sic1.bits.hpd = 0;				/* Handset Bias Power Down */
			j->sic1.bits.lpd = 0;				/* Line Bias Power Down */
			j->sic1.bits.spd = 1;				/* Speaker Drive Power Down */
			j->psccr.bits.addr = 1;				/* R/W Smart Cable Register Address */
			j->psccr.bits.rw = 0;				/* Read / Write flag */
			j->psccr.bits.dev = 0;
			outb(j->sic1.byte, j->XILINXbase + 0x00);
			outb(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);

			j->sic2.bits.al = 0;				/* Analog Loopback DAC analog -> ADC analog */
			j->sic2.bits.dl2 = 0;				/* Digital Loopback DAC -> ADC one bit */
			j->sic2.bits.dl1 = 0;				/* Digital Loopback ADC -> DAC one bit */
			j->sic2.bits.pll = 0;				/* 1 = div 10, 0 = div 5 */
			j->sic2.bits.hpd = 0;				/* HPF disable */
			j->psccr.bits.addr = 2;				/* R/W Smart Cable Register Address */
			j->psccr.bits.rw = 0;				/* Read / Write flag */
			j->psccr.bits.dev = 0;
			outb(j->sic2.byte, j->XILINXbase + 0x00);
			outb(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);

			j->psccr.bits.addr = 3;				/* R/W Smart Cable Register Address */
			j->psccr.bits.rw = 0;				/* Read / Write flag */
			j->psccr.bits.dev = 0;
			outb(0x00, j->XILINXbase + 0x00);		/* PLL Divide N1 */
			outb(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);

			j->psccr.bits.addr = 4;				/* R/W Smart Cable Register Address */
			j->psccr.bits.rw = 0;				/* Read / Write flag */
			j->psccr.bits.dev = 0;
			outb(0x09, j->XILINXbase + 0x00);		/* PLL Multiply M1 */
			outb(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);

			j->sirxg.bits.lig = 1;				/* Line In Gain */
			j->sirxg.bits.lim = 1;				/* Line In Mute */
			j->sirxg.bits.mcg = 0;				/* MIC In Gain was 3 */
			j->sirxg.bits.mcm = 0;				/* MIC In Mute */
			j->sirxg.bits.him = 0;				/* Handset In Mute */
			j->sirxg.bits.iir = 1;				/* IIR */
			j->psccr.bits.addr = 5;				/* R/W Smart Cable Register Address */
			j->psccr.bits.rw = 0;				/* Read / Write flag */
			j->psccr.bits.dev = 0;
			outb(j->sirxg.byte, j->XILINXbase + 0x00);
			outb(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);

			ixj_siadc(j, 0x17);
			ixj_sidac(j, 0x1D);

			j->siaatt.bits.sot = 0;
			j->psccr.bits.addr = 9;				/* R/W Smart Cable Register Address */
			j->psccr.bits.rw = 0;				/* Read / Write flag */
			j->psccr.bits.dev = 0;
			outb(j->siaatt.byte, j->XILINXbase + 0x00);
			outb(j->psccr.byte, j->XILINXbase + 0x01);
			ixj_PCcontrol_wait(j);

			if (j->flags.pcmciasct == 1 && !j->readers && !j->writers) {
				j->psccr.byte = j->pslic.byte = 0;
				j->pslic.bits.powerdown = 1;
				j->psccr.bits.dev = 3;
				j->psccr.bits.rw = 0;
				outw_p(j->psccr.byte << 8 | j->pslic.byte, j->XILINXbase + 0x00);
				ixj_PCcontrol_wait(j);
			}
		}
		return 0;
	} else {
		j->flags.pcmciascp = 0;
		return 0;
	}
	return 0;
}