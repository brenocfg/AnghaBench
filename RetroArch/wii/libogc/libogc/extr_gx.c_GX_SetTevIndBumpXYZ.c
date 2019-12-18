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
 int /*<<< orphan*/  GX_ITBA_OFF ; 
 int /*<<< orphan*/  GX_ITB_STU ; 
 int /*<<< orphan*/  GX_ITF_8 ; 
 int /*<<< orphan*/  GX_ITW_OFF ; 
 int /*<<< orphan*/  GX_SetTevIndirect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void GX_SetTevIndBumpXYZ(u8 tevstage,u8 indstage,u8 mtx_sel)
{
	GX_SetTevIndirect(tevstage,indstage,GX_ITF_8,GX_ITB_STU,mtx_sel,GX_ITW_OFF,GX_ITW_OFF,GX_FALSE,GX_FALSE,GX_ITBA_OFF);
}