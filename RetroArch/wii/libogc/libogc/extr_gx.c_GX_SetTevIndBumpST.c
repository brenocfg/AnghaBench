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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_ITBA_OFF ; 
 int /*<<< orphan*/  GX_ITB_NONE ; 
 int /*<<< orphan*/  GX_ITB_ST ; 
 int /*<<< orphan*/  GX_ITF_8 ; 
#define  GX_ITM_0 130 
#define  GX_ITM_1 129 
#define  GX_ITM_2 128 
 int GX_ITM_OFF ; 
 int GX_ITM_S0 ; 
 int GX_ITM_S1 ; 
 int GX_ITM_S2 ; 
 int GX_ITM_T0 ; 
 int GX_ITM_T1 ; 
 int GX_ITM_T2 ; 
 int /*<<< orphan*/  GX_ITW_0 ; 
 int /*<<< orphan*/  GX_ITW_OFF ; 
 int /*<<< orphan*/  GX_SetTevIndirect (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TRUE ; 

void GX_SetTevIndBumpST(u8 tevstage,u8 indstage,u8 mtx_sel)
{
	u8 sel_s,sel_t;

	switch(mtx_sel) {
		case GX_ITM_0:
			sel_s = GX_ITM_S0;
			sel_t = GX_ITM_T0;
			break;
		case GX_ITM_1:
			sel_s = GX_ITM_S1;
			sel_t = GX_ITM_T1;
			break;
		case GX_ITM_2:
			sel_s = GX_ITM_S2;
			sel_t = GX_ITM_T2;
			break;
		default:
			sel_s = GX_ITM_OFF;
			sel_t = GX_ITM_OFF;
			break;
	}

	GX_SetTevIndirect((tevstage+0),indstage,GX_ITF_8,GX_ITB_ST,sel_s,GX_ITW_0,GX_ITW_0,GX_FALSE,GX_FALSE,GX_ITBA_OFF);
	GX_SetTevIndirect((tevstage+1),indstage,GX_ITF_8,GX_ITB_ST,sel_t,GX_ITW_0,GX_ITW_0,GX_TRUE,GX_FALSE,GX_ITBA_OFF);
	GX_SetTevIndirect((tevstage+2),indstage,GX_ITF_8,GX_ITB_NONE,GX_ITM_OFF,GX_ITW_OFF,GX_ITW_OFF,GX_TRUE,GX_FALSE,GX_ITBA_OFF);
}