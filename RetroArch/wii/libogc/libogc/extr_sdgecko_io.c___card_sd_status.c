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
typedef  size_t s32 ;

/* Variables and functions */
 size_t CARDIO_ERROR_NOCARD ; 
 size_t MAX_DRIVE ; 
 size_t __card_dataread (size_t,int /*<<< orphan*/ ,int) ; 
 size_t __card_response2 (size_t) ; 
 size_t __card_sendappcmd (size_t) ; 
 size_t __card_sendcmd (size_t,int,int /*<<< orphan*/ *) ; 
 size_t __card_setblocklen (size_t,int) ; 
 int* _ioPageSize ; 
 int /*<<< orphan*/ * g_CardStatus ; 

__attribute__((used)) static s32 __card_sd_status(s32 drv_no)
{
	s32 ret;

	if(drv_no<0 || drv_no>=MAX_DRIVE) return CARDIO_ERROR_NOCARD;
	if(_ioPageSize[drv_no]!=64) {
		_ioPageSize[drv_no] = 64;
		if((ret=__card_setblocklen(drv_no,_ioPageSize[drv_no]))!=0) return ret;
	}
	if((ret=__card_sendappcmd(drv_no))!=0) return ret;
	if((ret=__card_sendcmd(drv_no,0x0d,NULL))!=0) return ret;
	if((ret=__card_response2(drv_no))!=0) return ret;
	ret = __card_dataread(drv_no,g_CardStatus[drv_no],64);

	return ret;
}