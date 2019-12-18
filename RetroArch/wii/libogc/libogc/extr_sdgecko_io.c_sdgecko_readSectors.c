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
typedef  int u32 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ CARDIO_ERROR_INTERNAL ; 
 scalar_t__ CARDIO_ERROR_NOCARD ; 
 scalar_t__ MAX_DRIVE ; 
 scalar_t__ PAGE_SIZE512 ; 
 scalar_t__ __card_dataread (scalar_t__,char*,scalar_t__) ; 
 scalar_t__ __card_response1 (scalar_t__) ; 
 scalar_t__ __card_sendcmd (scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ __card_setblocklen (scalar_t__,scalar_t__) ; 
 scalar_t__ __card_stopresponse (scalar_t__) ; 
 int /*<<< orphan*/  __convert_sector (scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__* _ioPageSize ; 
 scalar_t__ sdgecko_preIO (scalar_t__) ; 

s32 sdgecko_readSectors(s32 drv_no,u32 sector_no,u32 num_sectors,void *buf)
{
	u32 i;
	s32 ret;
	u8 arg[4];
	char *ptr = (char*)buf;

	if(drv_no<0 || drv_no>=MAX_DRIVE) return CARDIO_ERROR_NOCARD;

	ret = sdgecko_preIO(drv_no);
	if(ret!=0) return ret;

	if(num_sectors<1) return CARDIO_ERROR_INTERNAL;

	// Must be 512b, otherwise fail!
	if(PAGE_SIZE512!=_ioPageSize[drv_no]) {
		_ioPageSize[drv_no] = PAGE_SIZE512;
		if((ret=__card_setblocklen(drv_no,PAGE_SIZE512))!=0) return ret;
	}

	// SDHC support fix
	__convert_sector(drv_no,sector_no,arg);

	if((ret=__card_sendcmd(drv_no,0x12,arg))!=0) return ret;
	if((ret=__card_response1(drv_no))!=0) return ret;

	for(i=0;i<num_sectors;i++) {
		if((ret=__card_dataread(drv_no,ptr,_ioPageSize[drv_no]))!=0) return ret;
		ptr += _ioPageSize[drv_no];
	}

	if((ret=__card_sendcmd(drv_no,0x0C,NULL))!=0) return ret;
	return __card_stopresponse(drv_no);
}