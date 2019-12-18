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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  GX_FALSE ; 
 int /*<<< orphan*/  GX_INDTEXSTAGE0 ; 
 int /*<<< orphan*/  GX_ITBA_OFF ; 
 int /*<<< orphan*/  GX_ITB_NONE ; 
 int /*<<< orphan*/  GX_ITF_8 ; 
 int /*<<< orphan*/  GX_ITM_OFF ; 
 int /*<<< orphan*/  GX_ITW_0 ; 
 int /*<<< orphan*/  GX_SetTevIndirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GX_TRUE ; 

void GX_SetTevIndRepeat(u8 tevstage)
{
	GX_SetTevIndirect(tevstage,GX_INDTEXSTAGE0,GX_ITF_8,GX_ITB_NONE,GX_ITM_OFF,GX_ITW_0,GX_ITW_0,GX_TRUE,GX_FALSE,GX_ITBA_OFF);
}