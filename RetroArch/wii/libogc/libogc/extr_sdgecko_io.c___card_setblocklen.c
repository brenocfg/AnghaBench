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
typedef  int u32 ;
typedef  size_t s32 ;

/* Variables and functions */
 size_t CARDIO_ERROR_NOCARD ; 
 size_t MAX_DRIVE ; 
 int PAGE_SIZE512 ; 
 size_t __card_readresponse (size_t,int /*<<< orphan*/ *,int) ; 
 size_t __card_writecmd (size_t,int*,int) ; 
 size_t __check_response (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** _ioResponse ; 

__attribute__((used)) static s32 __card_setblocklen(s32 drv_no,u32 block_len)
{
	u8 cmd[5];
	s32 ret;

	if(drv_no<0 || drv_no>=MAX_DRIVE) return CARDIO_ERROR_NOCARD;
	if(block_len>PAGE_SIZE512) block_len = PAGE_SIZE512;

	cmd[0] = 0x10;
	cmd[1] = (block_len>>24)&0xff;
	cmd[2] = (block_len>>16)&0xff;
	cmd[3] = (block_len>>8)&0xff;
	cmd[4] = block_len&0xff;
	if((ret=__card_writecmd(drv_no,cmd,5))!=0) {
		return ret;
	}
	if((ret=__card_readresponse(drv_no,_ioResponse[drv_no],1))<0) return ret;
	ret = __check_response(drv_no,_ioResponse[drv_no][0]);

	return ret;
}