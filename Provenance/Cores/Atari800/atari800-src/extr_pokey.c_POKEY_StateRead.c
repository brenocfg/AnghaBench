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
typedef  int /*<<< orphan*/  UWORD ;

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
 scalar_t__ POKEY_OFFSET_AUDC1 ; 
 int /*<<< orphan*/  POKEY_OFFSET_AUDCTL ; 
 scalar_t__ POKEY_OFFSET_AUDF1 ; 
 int /*<<< orphan*/  POKEY_PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POKEY_SKCTL ; 
 int /*<<< orphan*/  StateSav_ReadINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int /*<<< orphan*/ *,int) ; 

void POKEY_StateRead(void)
{
	int i;
	int shift_key;
	int keypressed;

	StateSav_ReadUBYTE(&POKEY_KBCODE, 1);
	StateSav_ReadUBYTE(&POKEY_IRQST, 1);
	StateSav_ReadUBYTE(&POKEY_IRQEN, 1);
	StateSav_ReadUBYTE(&POKEY_SKCTL, 1);

	StateSav_ReadINT(&shift_key, 1);
	StateSav_ReadINT(&keypressed, 1);
	StateSav_ReadINT(&POKEY_DELAYED_SERIN_IRQ, 1);
	StateSav_ReadINT(&POKEY_DELAYED_SEROUT_IRQ, 1);
	StateSav_ReadINT(&POKEY_DELAYED_XMTDONE_IRQ, 1);

	StateSav_ReadUBYTE(&POKEY_AUDF[0], 4);
	StateSav_ReadUBYTE(&POKEY_AUDC[0], 4);
	StateSav_ReadUBYTE(&POKEY_AUDCTL[0], 1);
	for (i = 0; i < 4; i++) {
		POKEY_PutByte((UWORD) (POKEY_OFFSET_AUDF1 + i * 2), POKEY_AUDF[i]);
		POKEY_PutByte((UWORD) (POKEY_OFFSET_AUDC1 + i * 2), POKEY_AUDC[i]);
	}
	POKEY_PutByte(POKEY_OFFSET_AUDCTL, POKEY_AUDCTL[0]);

	StateSav_ReadINT(&POKEY_DivNIRQ[0], 4);
	StateSav_ReadINT(&POKEY_DivNMax[0], 4);
	StateSav_ReadINT(&POKEY_Base_mult[0], 1);
}