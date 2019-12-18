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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ EXI_Attach (scalar_t__,int /*<<< orphan*/ ) ; 
 int EXI_FLAG_ATTACH ; 
 int EXI_GetState (scalar_t__) ; 
 scalar_t__ EXI_ProbeEx (scalar_t__) ; 
 int FALSE ; 
 scalar_t__ MAX_DRIVE ; 
 int TRUE ; 
 int /*<<< orphan*/  __card_exthandler ; 
 int /*<<< orphan*/  sdgecko_insertedCB (scalar_t__) ; 

__attribute__((used)) static bool __card_check(s32 drv_no)
{
	s32 ret;

	if(drv_no<0 || drv_no>=MAX_DRIVE) return FALSE;
	while((ret=EXI_ProbeEx(drv_no))==0);
	if(ret!=1) return FALSE;

	if(!(EXI_GetState(drv_no)&EXI_FLAG_ATTACH)) {
		if(EXI_Attach(drv_no,__card_exthandler)==0) return FALSE;
		sdgecko_insertedCB(drv_no);
	}
	return TRUE;
}