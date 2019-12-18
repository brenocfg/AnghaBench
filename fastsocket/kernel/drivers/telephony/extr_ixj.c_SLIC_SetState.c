#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int c1; int c2; int c3; int b2en; } ;
struct TYPE_16__ {int /*<<< orphan*/  byte; TYPE_7__ bits; } ;
struct TYPE_12__ {int powerdown; int ring0; int ring1; } ;
struct TYPE_15__ {int byte; TYPE_2__ bits; } ;
struct TYPE_13__ {int dev; scalar_t__ rw; } ;
struct TYPE_14__ {int byte; TYPE_3__ bits; } ;
struct TYPE_11__ {scalar_t__ pcmciasct; } ;
struct TYPE_18__ {scalar_t__ cardtype; scalar_t__ XILINXbase; TYPE_6__ pld_slicw; TYPE_5__ pslic; TYPE_4__ psccr; int /*<<< orphan*/  writers; int /*<<< orphan*/  readers; TYPE_1__ flags; } ;
typedef  TYPE_8__ IXJ ;
typedef  int BYTE ;

/* Variables and functions */
#define  PLD_SLIC_STATE_ACTIVE 135 
#define  PLD_SLIC_STATE_APR 134 
#define  PLD_SLIC_STATE_OC 133 
#define  PLD_SLIC_STATE_OHT 132 
#define  PLD_SLIC_STATE_OHTPR 131 
#define  PLD_SLIC_STATE_RINGING 130 
#define  PLD_SLIC_STATE_STANDBY 129 
#define  PLD_SLIC_STATE_TIPOPEN 128 
 scalar_t__ QTI_PHONECARD ; 
 int /*<<< orphan*/  ixj_PCcontrol_wait (TYPE_8__*) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw_p (int,scalar_t__) ; 

__attribute__((used)) static bool SLIC_SetState(BYTE byState, IXJ *j)
{
	bool fRetVal = false;

	if (j->cardtype == QTI_PHONECARD) {
		if (j->flags.pcmciasct) {
			switch (byState) {
			case PLD_SLIC_STATE_TIPOPEN:
			case PLD_SLIC_STATE_OC:
				j->pslic.bits.powerdown = 1;
				j->pslic.bits.ring0 = j->pslic.bits.ring1 = 0;
				fRetVal = true;
				break;
			case PLD_SLIC_STATE_RINGING:
				if (j->readers || j->writers) {
					j->pslic.bits.powerdown = 0;
					j->pslic.bits.ring0 = 1;
					j->pslic.bits.ring1 = 0;
					fRetVal = true;
				}
				break;
			case PLD_SLIC_STATE_OHT:	/* On-hook transmit */

			case PLD_SLIC_STATE_STANDBY:
			case PLD_SLIC_STATE_ACTIVE:
				if (j->readers || j->writers) {
					j->pslic.bits.powerdown = 0;
				} else {
					j->pslic.bits.powerdown = 1;
				}
				j->pslic.bits.ring0 = j->pslic.bits.ring1 = 0;
				fRetVal = true;
				break;
			case PLD_SLIC_STATE_APR:	/* Active polarity reversal */

			case PLD_SLIC_STATE_OHTPR:	/* OHT polarity reversal */

			default:
				fRetVal = false;
				break;
			}
			j->psccr.bits.dev = 3;
			j->psccr.bits.rw = 0;
			outw_p(j->psccr.byte << 8 | j->pslic.byte, j->XILINXbase + 0x00);
			ixj_PCcontrol_wait(j);
		}
	} else {
		/* Set the C1, C2, C3 & B2EN signals. */
		switch (byState) {
		case PLD_SLIC_STATE_OC:
			j->pld_slicw.bits.c1 = 0;
			j->pld_slicw.bits.c2 = 0;
			j->pld_slicw.bits.c3 = 0;
			j->pld_slicw.bits.b2en = 0;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		case PLD_SLIC_STATE_RINGING:
			j->pld_slicw.bits.c1 = 1;
			j->pld_slicw.bits.c2 = 0;
			j->pld_slicw.bits.c3 = 0;
			j->pld_slicw.bits.b2en = 1;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		case PLD_SLIC_STATE_ACTIVE:
			j->pld_slicw.bits.c1 = 0;
			j->pld_slicw.bits.c2 = 1;
			j->pld_slicw.bits.c3 = 0;
			j->pld_slicw.bits.b2en = 0;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		case PLD_SLIC_STATE_OHT:	/* On-hook transmit */

			j->pld_slicw.bits.c1 = 1;
			j->pld_slicw.bits.c2 = 1;
			j->pld_slicw.bits.c3 = 0;
			j->pld_slicw.bits.b2en = 0;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		case PLD_SLIC_STATE_TIPOPEN:
			j->pld_slicw.bits.c1 = 0;
			j->pld_slicw.bits.c2 = 0;
			j->pld_slicw.bits.c3 = 1;
			j->pld_slicw.bits.b2en = 0;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		case PLD_SLIC_STATE_STANDBY:
			j->pld_slicw.bits.c1 = 1;
			j->pld_slicw.bits.c2 = 0;
			j->pld_slicw.bits.c3 = 1;
			j->pld_slicw.bits.b2en = 1;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		case PLD_SLIC_STATE_APR:	/* Active polarity reversal */

			j->pld_slicw.bits.c1 = 0;
			j->pld_slicw.bits.c2 = 1;
			j->pld_slicw.bits.c3 = 1;
			j->pld_slicw.bits.b2en = 0;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		case PLD_SLIC_STATE_OHTPR:	/* OHT polarity reversal */

			j->pld_slicw.bits.c1 = 1;
			j->pld_slicw.bits.c2 = 1;
			j->pld_slicw.bits.c3 = 1;
			j->pld_slicw.bits.b2en = 0;
			outb_p(j->pld_slicw.byte, j->XILINXbase + 0x01);
			fRetVal = true;
			break;
		default:
			fRetVal = false;
			break;
		}
	}

	return fRetVal;
}