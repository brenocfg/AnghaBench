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
typedef  size_t s32 ;

/* Variables and functions */
 size_t CARDIO_OP_IOERR_CRC ; 
 size_t CARDIO_OP_IOERR_WRITE ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 size_t __card_datares (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** _ioResponse ; 

__attribute__((used)) static s32 __card_dataresponse(s32 drv_no)
{
	s32 ret;
	u8 res;

	if((ret=__card_datares(drv_no,_ioResponse[drv_no]))!=0) return ret;
	res = _SHIFTR(_ioResponse[drv_no][0],1,3);
	if(res==0x0005) ret = CARDIO_OP_IOERR_CRC;
	else if(res==0x0006) ret = CARDIO_OP_IOERR_WRITE;

	return ret;
}