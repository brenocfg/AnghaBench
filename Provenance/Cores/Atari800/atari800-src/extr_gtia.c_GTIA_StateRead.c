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
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  GTIA_COLBK ; 
 int /*<<< orphan*/  GTIA_COLPF0 ; 
 int /*<<< orphan*/  GTIA_COLPF1 ; 
 int /*<<< orphan*/  GTIA_COLPF2 ; 
 int /*<<< orphan*/  GTIA_COLPF3 ; 
 int /*<<< orphan*/  GTIA_COLPM0 ; 
 int /*<<< orphan*/  GTIA_COLPM1 ; 
 int /*<<< orphan*/  GTIA_COLPM2 ; 
 int /*<<< orphan*/  GTIA_COLPM3 ; 
 int /*<<< orphan*/  GTIA_GRACTL ; 
 int /*<<< orphan*/  GTIA_GRAFM ; 
 int /*<<< orphan*/  GTIA_GRAFP0 ; 
 int /*<<< orphan*/  GTIA_GRAFP1 ; 
 int /*<<< orphan*/  GTIA_GRAFP2 ; 
 int /*<<< orphan*/  GTIA_GRAFP3 ; 
 int /*<<< orphan*/  GTIA_HPOSM0 ; 
 int /*<<< orphan*/  GTIA_HPOSM1 ; 
 int /*<<< orphan*/  GTIA_HPOSM2 ; 
 int /*<<< orphan*/  GTIA_HPOSM3 ; 
 int /*<<< orphan*/  GTIA_HPOSP0 ; 
 int /*<<< orphan*/  GTIA_HPOSP1 ; 
 int /*<<< orphan*/  GTIA_HPOSP2 ; 
 int /*<<< orphan*/  GTIA_HPOSP3 ; 
 int /*<<< orphan*/  GTIA_M0PL ; 
 int /*<<< orphan*/  GTIA_M1PL ; 
 int /*<<< orphan*/  GTIA_M2PL ; 
 int /*<<< orphan*/  GTIA_M3PL ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLBK ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPF0 ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPF1 ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPF2 ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPF3 ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPM0 ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPM1 ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPM2 ; 
 int /*<<< orphan*/  GTIA_OFFSET_COLPM3 ; 
 int /*<<< orphan*/  GTIA_OFFSET_GRACTL ; 
 int /*<<< orphan*/  GTIA_OFFSET_GRAFM ; 
 int /*<<< orphan*/  GTIA_OFFSET_GRAFP0 ; 
 int /*<<< orphan*/  GTIA_OFFSET_GRAFP1 ; 
 int /*<<< orphan*/  GTIA_OFFSET_GRAFP2 ; 
 int /*<<< orphan*/  GTIA_OFFSET_GRAFP3 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSM0 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSM1 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSM2 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSM3 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSP0 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSP1 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSP2 ; 
 int /*<<< orphan*/  GTIA_OFFSET_HPOSP3 ; 
 int /*<<< orphan*/  GTIA_OFFSET_PRIOR ; 
 int /*<<< orphan*/  GTIA_OFFSET_SIZEM ; 
 int /*<<< orphan*/  GTIA_OFFSET_SIZEP0 ; 
 int /*<<< orphan*/  GTIA_OFFSET_SIZEP1 ; 
 int /*<<< orphan*/  GTIA_OFFSET_SIZEP2 ; 
 int /*<<< orphan*/  GTIA_OFFSET_SIZEP3 ; 
 int /*<<< orphan*/  GTIA_P0PL ; 
 int /*<<< orphan*/  GTIA_P1PL ; 
 int /*<<< orphan*/  GTIA_P2PL ; 
 int /*<<< orphan*/  GTIA_P3PL ; 
 int /*<<< orphan*/  GTIA_PRIOR ; 
 int /*<<< orphan*/  GTIA_PutByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTIA_SIZEM ; 
 int /*<<< orphan*/  GTIA_SIZEP0 ; 
 int /*<<< orphan*/  GTIA_SIZEP1 ; 
 int /*<<< orphan*/  GTIA_SIZEP2 ; 
 int /*<<< orphan*/  GTIA_SIZEP3 ; 
 int /*<<< orphan*/ * GTIA_TRIG_latch ; 
 int /*<<< orphan*/  GTIA_VDELAY ; 
 int GTIA_speaker ; 
 int /*<<< orphan*/  PF0PM ; 
 int /*<<< orphan*/  PF1PM ; 
 int /*<<< orphan*/  PF2PM ; 
 int /*<<< orphan*/  PF3PM ; 
 int /*<<< orphan*/  StateSav_ReadINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_ReadUBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  consol_mask ; 

void GTIA_StateRead(UBYTE version)
{
	int next_console_value;	/* ignored */

	StateSav_ReadUBYTE(&GTIA_HPOSP0, 1);
	StateSav_ReadUBYTE(&GTIA_HPOSP1, 1);
	StateSav_ReadUBYTE(&GTIA_HPOSP2, 1);
	StateSav_ReadUBYTE(&GTIA_HPOSP3, 1);
	StateSav_ReadUBYTE(&GTIA_HPOSM0, 1);
	StateSav_ReadUBYTE(&GTIA_HPOSM1, 1);
	StateSav_ReadUBYTE(&GTIA_HPOSM2, 1);
	StateSav_ReadUBYTE(&GTIA_HPOSM3, 1);
	StateSav_ReadUBYTE(&PF0PM, 1);
	StateSav_ReadUBYTE(&PF1PM, 1);
	StateSav_ReadUBYTE(&PF2PM, 1);
	StateSav_ReadUBYTE(&PF3PM, 1);
	StateSav_ReadUBYTE(&GTIA_M0PL, 1);
	StateSav_ReadUBYTE(&GTIA_M1PL, 1);
	StateSav_ReadUBYTE(&GTIA_M2PL, 1);
	StateSav_ReadUBYTE(&GTIA_M3PL, 1);
	StateSav_ReadUBYTE(&GTIA_P0PL, 1);
	StateSav_ReadUBYTE(&GTIA_P1PL, 1);
	StateSav_ReadUBYTE(&GTIA_P2PL, 1);
	StateSav_ReadUBYTE(&GTIA_P3PL, 1);
	StateSav_ReadUBYTE(&GTIA_SIZEP0, 1);
	StateSav_ReadUBYTE(&GTIA_SIZEP1, 1);
	StateSav_ReadUBYTE(&GTIA_SIZEP2, 1);
	StateSav_ReadUBYTE(&GTIA_SIZEP3, 1);
	StateSav_ReadUBYTE(&GTIA_SIZEM, 1);
	StateSav_ReadUBYTE(&GTIA_GRAFP0, 1);
	StateSav_ReadUBYTE(&GTIA_GRAFP1, 1);
	StateSav_ReadUBYTE(&GTIA_GRAFP2, 1);
	StateSav_ReadUBYTE(&GTIA_GRAFP3, 1);
	StateSav_ReadUBYTE(&GTIA_GRAFM, 1);
	StateSav_ReadUBYTE(&GTIA_COLPM0, 1);
	StateSav_ReadUBYTE(&GTIA_COLPM1, 1);
	StateSav_ReadUBYTE(&GTIA_COLPM2, 1);
	StateSav_ReadUBYTE(&GTIA_COLPM3, 1);
	StateSav_ReadUBYTE(&GTIA_COLPF0, 1);
	StateSav_ReadUBYTE(&GTIA_COLPF1, 1);
	StateSav_ReadUBYTE(&GTIA_COLPF2, 1);
	StateSav_ReadUBYTE(&GTIA_COLPF3, 1);
	StateSav_ReadUBYTE(&GTIA_COLBK, 1);
	StateSav_ReadUBYTE(&GTIA_PRIOR, 1);
	StateSav_ReadUBYTE(&GTIA_VDELAY, 1);
	StateSav_ReadUBYTE(&GTIA_GRACTL, 1);

	StateSav_ReadUBYTE(&consol_mask, 1);
	StateSav_ReadINT(&GTIA_speaker, 1);
	StateSav_ReadINT(&next_console_value, 1);
	if (version >= 7)
		StateSav_ReadUBYTE(GTIA_TRIG_latch, 4);

	GTIA_PutByte(GTIA_OFFSET_HPOSP0, GTIA_HPOSP0);
	GTIA_PutByte(GTIA_OFFSET_HPOSP1, GTIA_HPOSP1);
	GTIA_PutByte(GTIA_OFFSET_HPOSP2, GTIA_HPOSP2);
	GTIA_PutByte(GTIA_OFFSET_HPOSP3, GTIA_HPOSP3);
	GTIA_PutByte(GTIA_OFFSET_HPOSM0, GTIA_HPOSM0);
	GTIA_PutByte(GTIA_OFFSET_HPOSM1, GTIA_HPOSM1);
	GTIA_PutByte(GTIA_OFFSET_HPOSM2, GTIA_HPOSM2);
	GTIA_PutByte(GTIA_OFFSET_HPOSM3, GTIA_HPOSM3);
	GTIA_PutByte(GTIA_OFFSET_SIZEP0, GTIA_SIZEP0);
	GTIA_PutByte(GTIA_OFFSET_SIZEP1, GTIA_SIZEP1);
	GTIA_PutByte(GTIA_OFFSET_SIZEP2, GTIA_SIZEP2);
	GTIA_PutByte(GTIA_OFFSET_SIZEP3, GTIA_SIZEP3);
	GTIA_PutByte(GTIA_OFFSET_SIZEM, GTIA_SIZEM);
	GTIA_PutByte(GTIA_OFFSET_GRAFP0, GTIA_GRAFP0);
	GTIA_PutByte(GTIA_OFFSET_GRAFP1, GTIA_GRAFP1);
	GTIA_PutByte(GTIA_OFFSET_GRAFP2, GTIA_GRAFP2);
	GTIA_PutByte(GTIA_OFFSET_GRAFP3, GTIA_GRAFP3);
	GTIA_PutByte(GTIA_OFFSET_GRAFM, GTIA_GRAFM);
	GTIA_PutByte(GTIA_OFFSET_COLPM0, GTIA_COLPM0);
	GTIA_PutByte(GTIA_OFFSET_COLPM1, GTIA_COLPM1);
	GTIA_PutByte(GTIA_OFFSET_COLPM2, GTIA_COLPM2);
	GTIA_PutByte(GTIA_OFFSET_COLPM3, GTIA_COLPM3);
	GTIA_PutByte(GTIA_OFFSET_COLPF0, GTIA_COLPF0);
	GTIA_PutByte(GTIA_OFFSET_COLPF1, GTIA_COLPF1);
	GTIA_PutByte(GTIA_OFFSET_COLPF2, GTIA_COLPF2);
	GTIA_PutByte(GTIA_OFFSET_COLPF3, GTIA_COLPF3);
	GTIA_PutByte(GTIA_OFFSET_COLBK, GTIA_COLBK);
	GTIA_PutByte(GTIA_OFFSET_PRIOR, GTIA_PRIOR);
	GTIA_PutByte(GTIA_OFFSET_GRACTL, GTIA_GRACTL);
}