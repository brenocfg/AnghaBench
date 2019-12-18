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
typedef  int /*<<< orphan*/  vortex_t ;
typedef  int u32 ;

/* Variables and functions */
 int NR_WT ; 
 int NR_WT_PB ; 
 int /*<<< orphan*/  vortex_wt_SetReg (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void vortex_wt_init(vortex_t * vortex)
{
	u32 var4, var8, varc, var10 = 0, edi;

	var10 &= 0xFFFFFFE3;
	var10 |= 0x22;
	var10 &= 0xFFFFFEBF;
	var10 |= 0x80;
	var10 |= 0x200;
	var10 &= 0xfffffffe;
	var10 &= 0xfffffbff;
	var10 |= 0x1800;
	// var10 = 0x1AA2
	var4 = 0x10000000;
	varc = 0x00830000;
	var8 = 0x00830000;

	/* Init Bank registers. */
	for (edi = 0; edi < (NR_WT / NR_WT_PB); edi++) {
		vortex_wt_SetReg(vortex, 0xc, edi, 0);	/* ds_reg */
		vortex_wt_SetReg(vortex, 0xa, edi, var10);	/* ctrl  */
		vortex_wt_SetReg(vortex, 0x9, edi, var4);	/* mramp */
		vortex_wt_SetReg(vortex, 0x8, edi, varc);	/* aramp */
		vortex_wt_SetReg(vortex, 0x5, edi, var8);	/* sramp */
	}
	/* Init Voice registers. */
	for (edi = 0; edi < NR_WT; edi++) {
		vortex_wt_SetReg(vortex, 0x4, edi, 0);	/* param 3 0x20c */
		vortex_wt_SetReg(vortex, 0x3, edi, 0);	/* param 2 0x208 */
		vortex_wt_SetReg(vortex, 0x2, edi, 0);	/* param 1 0x204 */
		vortex_wt_SetReg(vortex, 0x1, edi, 0);	/* param 0 0x200 */
		vortex_wt_SetReg(vortex, 0xb, edi, 0);	/* delay 0x400 - 0x40c */
	}
	var10 |= 1;
	for (edi = 0; edi < (NR_WT / NR_WT_PB); edi++)
		vortex_wt_SetReg(vortex, 0xa, edi, var10);	/* ctrl */
}