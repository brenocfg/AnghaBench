#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/ * POKEY_AUDC ; 
 int /*<<< orphan*/ * POKEY_AUDCTL ; 
 int /*<<< orphan*/ * POKEY_AUDF ; 
 int* POKEY_Base_mult ; 
 int POKEY_DELAYED_SERIN_IRQ ; 
 int POKEY_DELAYED_SEROUT_IRQ ; 
 int POKEY_DELAYED_XMTDONE_IRQ ; 
 int* POKEY_DivNIRQ ; 
 int* POKEY_DivNMax ; 
 int /*<<< orphan*/  POKEY_IRQEN ; 
 int /*<<< orphan*/  POKEY_IRQST ; 
 int /*<<< orphan*/  POKEY_KBCODE ; 
 int /*<<< orphan*/  POKEY_SKCTL ; 
 int /*<<< orphan*/  StateSav_SaveINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (int /*<<< orphan*/ *,int) ; 

void POKEY_StateSave(void)
{
	int shift_key = 0;
	int keypressed = 0;

	StateSav_SaveUBYTE(&POKEY_KBCODE, 1);
	StateSav_SaveUBYTE(&POKEY_IRQST, 1);
	StateSav_SaveUBYTE(&POKEY_IRQEN, 1);
	StateSav_SaveUBYTE(&POKEY_SKCTL, 1);

	StateSav_SaveINT(&shift_key, 1);
	StateSav_SaveINT(&keypressed, 1);
	StateSav_SaveINT(&POKEY_DELAYED_SERIN_IRQ, 1);
	StateSav_SaveINT(&POKEY_DELAYED_SEROUT_IRQ, 1);
	StateSav_SaveINT(&POKEY_DELAYED_XMTDONE_IRQ, 1);

	StateSav_SaveUBYTE(&POKEY_AUDF[0], 4);
	StateSav_SaveUBYTE(&POKEY_AUDC[0], 4);
	StateSav_SaveUBYTE(&POKEY_AUDCTL[0], 1);

	StateSav_SaveINT(&POKEY_DivNIRQ[0], 4);
	StateSav_SaveINT(&POKEY_DivNMax[0], 4);
	StateSav_SaveINT(&POKEY_Base_mult[0], 1);
}