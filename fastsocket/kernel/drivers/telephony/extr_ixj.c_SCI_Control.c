#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int c0; int c1; } ;
struct TYPE_7__ {int /*<<< orphan*/  byte; TYPE_1__ bits; } ;
struct TYPE_8__ {int /*<<< orphan*/  XILINXbase; TYPE_2__ pld_scrw; } ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
#define  SCI_Enable_DAA 131 
#define  SCI_Enable_EEPROM 130 
#define  SCI_Enable_Mixer 129 
#define  SCI_End 128 
 int /*<<< orphan*/  SCI_WaitHighSCI (TYPE_3__*) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SCI_Control(IXJ *j, int control)
{
	switch (control) {
	case SCI_End:
		j->pld_scrw.bits.c0 = 0;	/* Set PLD Serial control interface */

		j->pld_scrw.bits.c1 = 0;	/* to no selection */

		break;
	case SCI_Enable_DAA:
		j->pld_scrw.bits.c0 = 1;	/* Set PLD Serial control interface */

		j->pld_scrw.bits.c1 = 0;	/* to write to DAA */

		break;
	case SCI_Enable_Mixer:
		j->pld_scrw.bits.c0 = 0;	/* Set PLD Serial control interface */

		j->pld_scrw.bits.c1 = 1;	/* to write to mixer */

		break;
	case SCI_Enable_EEPROM:
		j->pld_scrw.bits.c0 = 1;	/* Set PLD Serial control interface */

		j->pld_scrw.bits.c1 = 1;	/* to write to EEPROM */

		break;
	default:
		return 0;
		break;
	}
	outb_p(j->pld_scrw.byte, j->XILINXbase);

	switch (control) {
	case SCI_End:
		return 1;
		break;
	case SCI_Enable_DAA:
	case SCI_Enable_Mixer:
	case SCI_Enable_EEPROM:
		if (!SCI_WaitHighSCI(j))
			return 0;
		break;
	default:
		return 0;
		break;
	}
	return 1;
}