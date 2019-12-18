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
 int /*<<< orphan*/  GTIA_P0PL ; 
 int /*<<< orphan*/  GTIA_P1PL ; 
 int /*<<< orphan*/  GTIA_P2PL ; 
 int /*<<< orphan*/  GTIA_P3PL ; 
 int /*<<< orphan*/  GTIA_PRIOR ; 
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
 int /*<<< orphan*/  StateSav_SaveINT (int*,int) ; 
 int /*<<< orphan*/  StateSav_SaveUBYTE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  consol_mask ; 

void GTIA_StateSave(void)
{
	int next_console_value = 7;

	StateSav_SaveUBYTE(&GTIA_HPOSP0, 1);
	StateSav_SaveUBYTE(&GTIA_HPOSP1, 1);
	StateSav_SaveUBYTE(&GTIA_HPOSP2, 1);
	StateSav_SaveUBYTE(&GTIA_HPOSP3, 1);
	StateSav_SaveUBYTE(&GTIA_HPOSM0, 1);
	StateSav_SaveUBYTE(&GTIA_HPOSM1, 1);
	StateSav_SaveUBYTE(&GTIA_HPOSM2, 1);
	StateSav_SaveUBYTE(&GTIA_HPOSM3, 1);
	StateSav_SaveUBYTE(&PF0PM, 1);
	StateSav_SaveUBYTE(&PF1PM, 1);
	StateSav_SaveUBYTE(&PF2PM, 1);
	StateSav_SaveUBYTE(&PF3PM, 1);
	StateSav_SaveUBYTE(&GTIA_M0PL, 1);
	StateSav_SaveUBYTE(&GTIA_M1PL, 1);
	StateSav_SaveUBYTE(&GTIA_M2PL, 1);
	StateSav_SaveUBYTE(&GTIA_M3PL, 1);
	StateSav_SaveUBYTE(&GTIA_P0PL, 1);
	StateSav_SaveUBYTE(&GTIA_P1PL, 1);
	StateSav_SaveUBYTE(&GTIA_P2PL, 1);
	StateSav_SaveUBYTE(&GTIA_P3PL, 1);
	StateSav_SaveUBYTE(&GTIA_SIZEP0, 1);
	StateSav_SaveUBYTE(&GTIA_SIZEP1, 1);
	StateSav_SaveUBYTE(&GTIA_SIZEP2, 1);
	StateSav_SaveUBYTE(&GTIA_SIZEP3, 1);
	StateSav_SaveUBYTE(&GTIA_SIZEM, 1);
	StateSav_SaveUBYTE(&GTIA_GRAFP0, 1);
	StateSav_SaveUBYTE(&GTIA_GRAFP1, 1);
	StateSav_SaveUBYTE(&GTIA_GRAFP2, 1);
	StateSav_SaveUBYTE(&GTIA_GRAFP3, 1);
	StateSav_SaveUBYTE(&GTIA_GRAFM, 1);
	StateSav_SaveUBYTE(&GTIA_COLPM0, 1);
	StateSav_SaveUBYTE(&GTIA_COLPM1, 1);
	StateSav_SaveUBYTE(&GTIA_COLPM2, 1);
	StateSav_SaveUBYTE(&GTIA_COLPM3, 1);
	StateSav_SaveUBYTE(&GTIA_COLPF0, 1);
	StateSav_SaveUBYTE(&GTIA_COLPF1, 1);
	StateSav_SaveUBYTE(&GTIA_COLPF2, 1);
	StateSav_SaveUBYTE(&GTIA_COLPF3, 1);
	StateSav_SaveUBYTE(&GTIA_COLBK, 1);
	StateSav_SaveUBYTE(&GTIA_PRIOR, 1);
	StateSav_SaveUBYTE(&GTIA_VDELAY, 1);
	StateSav_SaveUBYTE(&GTIA_GRACTL, 1);

	StateSav_SaveUBYTE(&consol_mask, 1);
	StateSav_SaveINT(&GTIA_speaker, 1);
	StateSav_SaveINT(&next_console_value, 1);
	StateSav_SaveUBYTE(GTIA_TRIG_latch, 4);
}