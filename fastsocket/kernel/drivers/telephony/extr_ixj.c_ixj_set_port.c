#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_27__ {int gpio6; int gpio7; } ;
struct TYPE_26__ {int high; } ;
struct TYPE_24__ {int rly1; int spken; int /*<<< orphan*/  rly3; } ;
struct TYPE_20__ {int mic; int spk; } ;
struct TYPE_25__ {int /*<<< orphan*/  byte; TYPE_6__ bits; TYPE_2__ pcib; } ;
struct TYPE_23__ {int /*<<< orphan*/  byte; } ;
struct TYPE_21__ {int /*<<< orphan*/  daafsyncen; } ;
struct TYPE_22__ {int /*<<< orphan*/  byte; TYPE_3__ bits; } ;
struct TYPE_19__ {int pcmciasct; } ;
struct TYPE_17__ {int word; TYPE_9__ bits; TYPE_8__ bytes; } ;
struct TYPE_18__ {scalar_t__ cardtype; int port; TYPE_10__ gpio; int /*<<< orphan*/  XILINXbase; TYPE_7__ pld_slicw; TYPE_5__ pld_clock; TYPE_4__ pld_scrw; TYPE_1__ flags; } ;
typedef  TYPE_11__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  PLD_SLIC_STATE_ACTIVE ; 
 int /*<<< orphan*/  PLD_SLIC_STATE_OC ; 
 int /*<<< orphan*/  PLD_SLIC_STATE_STANDBY ; 
#define  PORT_HANDSET 135 
#define  PORT_POTS 134 
#define  PORT_PSTN 133 
#define  PORT_SPEAKER 132 
#define  QTI_LINEJACK 131 
#define  QTI_PHONECARD 130 
#define  QTI_PHONEJACK 129 
 scalar_t__ QTI_PHONEJACK_LITE ; 
#define  QTI_PHONEJACK_PCI 128 
 int /*<<< orphan*/  SLIC_SetState (int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  ixj_WriteDSPCommand (int,TYPE_11__*) ; 
 int /*<<< orphan*/  ixj_mixer (int,TYPE_11__*) ; 
 int /*<<< orphan*/  ixj_set_pots (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixj_set_port(IXJ *j, int arg)
{
	if (j->cardtype == QTI_PHONEJACK_LITE) {
		if (arg != PORT_POTS)
			return 10;
		else
			return 0;
	}
	switch (arg) {
	case PORT_POTS:
		j->port = PORT_POTS;
		switch (j->cardtype) {
		case QTI_PHONECARD:
			if (j->flags.pcmciasct == 1)
				SLIC_SetState(PLD_SLIC_STATE_ACTIVE, j);
			else
				return 11;
			break;
		case QTI_PHONEJACK_PCI:
			j->pld_slicw.pcib.mic = 0;
			j->pld_slicw.pcib.spk = 0;
			outb(j->pld_slicw.byte, j->XILINXbase + 0x01);
			break;
		case QTI_LINEJACK:
			ixj_set_pots(j, 0);			/* Disconnect POTS/PSTN relay */
			if (ixj_WriteDSPCommand(0xC528, j))		/* Write CODEC config to
									   Software Control Register */
				return 2;
			j->pld_scrw.bits.daafsyncen = 0;	/* Turn off DAA Frame Sync */

			outb(j->pld_scrw.byte, j->XILINXbase);
			j->pld_clock.byte = 0;
			outb(j->pld_clock.byte, j->XILINXbase + 0x04);
			j->pld_slicw.bits.rly1 = 1;
			j->pld_slicw.bits.spken = 0;
			outb(j->pld_slicw.byte, j->XILINXbase + 0x01);
			ixj_mixer(0x1200, j);	/* Turn Off MIC switch on mixer left */
			ixj_mixer(0x1401, j);	/* Turn On Mono1 switch on mixer left */
			ixj_mixer(0x1300, j);       /* Turn Off MIC switch on mixer right */
			ixj_mixer(0x1501, j);       /* Turn On Mono1 switch on mixer right */
			ixj_mixer(0x0E80, j);	/*Mic mute */
			ixj_mixer(0x0F00, j);	/* Set mono out (SLIC) to 0dB */
			ixj_mixer(0x0080, j);	/* Mute Master Left volume */
			ixj_mixer(0x0180, j);	/* Mute Master Right volume */
			SLIC_SetState(PLD_SLIC_STATE_STANDBY, j);
/*			SLIC_SetState(PLD_SLIC_STATE_ACTIVE, j); */
			break;
		case QTI_PHONEJACK:
			j->gpio.bytes.high = 0x0B;
			j->gpio.bits.gpio6 = 0;
			j->gpio.bits.gpio7 = 0;
			ixj_WriteDSPCommand(j->gpio.word, j);
			break;
		}
		break;
	case PORT_PSTN:
		if (j->cardtype == QTI_LINEJACK) {
			ixj_WriteDSPCommand(0xC534, j);	/* Write CODEC config to Software Control Register */

			j->pld_slicw.bits.rly3 = 0;
			j->pld_slicw.bits.rly1 = 1;
			j->pld_slicw.bits.spken = 0;
			outb(j->pld_slicw.byte, j->XILINXbase + 0x01);
			j->port = PORT_PSTN;
		} else {
			return 4;
		}
		break;
	case PORT_SPEAKER:
		j->port = PORT_SPEAKER;
		switch (j->cardtype) {
		case QTI_PHONECARD:
			if (j->flags.pcmciasct) {
				SLIC_SetState(PLD_SLIC_STATE_OC, j);
			}
			break;
		case QTI_PHONEJACK_PCI:
			j->pld_slicw.pcib.mic = 1;
			j->pld_slicw.pcib.spk = 1;
			outb(j->pld_slicw.byte, j->XILINXbase + 0x01);
			break;
		case QTI_LINEJACK:
			ixj_set_pots(j, 0);			/* Disconnect POTS/PSTN relay */
			if (ixj_WriteDSPCommand(0xC528, j))		/* Write CODEC config to
									   Software Control Register */
				return 2;
			j->pld_scrw.bits.daafsyncen = 0;	/* Turn off DAA Frame Sync */

			outb(j->pld_scrw.byte, j->XILINXbase);
			j->pld_clock.byte = 0;
			outb(j->pld_clock.byte, j->XILINXbase + 0x04);
			j->pld_slicw.bits.rly1 = 1;
			j->pld_slicw.bits.spken = 1;
			outb(j->pld_slicw.byte, j->XILINXbase + 0x01);
			ixj_mixer(0x1201, j);	/* Turn On MIC switch on mixer left */
			ixj_mixer(0x1400, j);	/* Turn Off Mono1 switch on mixer left */
			ixj_mixer(0x1301, j);       /* Turn On MIC switch on mixer right */
			ixj_mixer(0x1500, j);       /* Turn Off Mono1 switch on mixer right */
			ixj_mixer(0x0E06, j);	/*Mic un-mute 0dB */
			ixj_mixer(0x0F80, j);	/* Mute mono out (SLIC) */
			ixj_mixer(0x0000, j);	/* Set Master Left volume to 0dB */
			ixj_mixer(0x0100, j);	/* Set Master Right volume to 0dB */
			break;
		case QTI_PHONEJACK:
			j->gpio.bytes.high = 0x0B;
			j->gpio.bits.gpio6 = 0;
			j->gpio.bits.gpio7 = 1;
			ixj_WriteDSPCommand(j->gpio.word, j);
			break;
		}
		break;
	case PORT_HANDSET:
		if (j->cardtype != QTI_PHONEJACK) {
			return 5;
		} else {
			j->gpio.bytes.high = 0x0B;
			j->gpio.bits.gpio6 = 1;
			j->gpio.bits.gpio7 = 0;
			ixj_WriteDSPCommand(j->gpio.word, j);
			j->port = PORT_HANDSET;
		}
		break;
	default:
		return 6;
		break;
	}
	return 0;
}