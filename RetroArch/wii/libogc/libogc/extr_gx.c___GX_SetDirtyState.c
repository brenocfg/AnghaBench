#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int dirtyState; } ;

/* Variables and functions */
 int /*<<< orphan*/  __GX_SetChanCntrl () ; 
 int /*<<< orphan*/  __GX_SetChanColor () ; 
 int /*<<< orphan*/  __GX_SetGenMode () ; 
 int /*<<< orphan*/  __GX_SetMatrixIndex (int) ; 
 int /*<<< orphan*/  __GX_SetSUTexRegs () ; 
 int /*<<< orphan*/  __GX_SetTexCoordGen () ; 
 int /*<<< orphan*/  __GX_SetVAT () ; 
 int /*<<< orphan*/  __GX_SetVCD () ; 
 int /*<<< orphan*/  __GX_UpdateBPMask () ; 
 TYPE_1__* __gx ; 

__attribute__((used)) static void __GX_SetDirtyState()
{
	if(__gx->dirtyState&0x0001) {
		__GX_SetSUTexRegs();
	}
	if(__gx->dirtyState&0x0002) {
		__GX_UpdateBPMask();
	}
	if(__gx->dirtyState&0x0004) {
		__GX_SetGenMode();
	}
	if(__gx->dirtyState&0x0008) {
		__GX_SetVCD();
	}
	if(__gx->dirtyState&0x0010) {
		__GX_SetVAT();
	}
	if(__gx->dirtyState&~0xff) {
		if(__gx->dirtyState&0x0f00) {
			__GX_SetChanColor();
		}
		if(__gx->dirtyState&0x0100f000) {
			__GX_SetChanCntrl();
		}
		if(__gx->dirtyState&0x02ff0000) {
			__GX_SetTexCoordGen();
		}
		if(__gx->dirtyState&0x04000000) {
			__GX_SetMatrixIndex(0);
			__GX_SetMatrixIndex(5);
		}
	}
	__gx->dirtyState = 0;
}