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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ CARDIO_ERROR_IOERROR ; 
 scalar_t__ CARDIO_ERROR_IOTIMEOUT ; 
 scalar_t__ CARDIO_ERROR_NOCARD ; 
 scalar_t__ CARDIO_ERROR_READY ; 
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 int /*<<< orphan*/  EXI_Deselect (scalar_t__) ; 
 scalar_t__ EXI_ImmEx (scalar_t__,int*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_READWRITE ; 
 scalar_t__ EXI_Select (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_Unlock (scalar_t__) ; 
 scalar_t__ MAX_DRIVE ; 
 scalar_t__ __card_checktimeout (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  __exi_wait (scalar_t__) ; 
 int /*<<< orphan*/  _ioCardFreq ; 
 int _ioClrFlag ; 
 scalar_t__ gettick () ; 

__attribute__((used)) static s32 __card_readresponse(s32 drv_no,void *buf,s32 len)
{
	u8 *ptr;
	s32 startT,ret;

	if(drv_no<0 || drv_no>=MAX_DRIVE) return CARDIO_ERROR_NOCARD;

	ret = CARDIO_ERROR_READY;
	ptr = buf;
	*ptr = _ioClrFlag;

	__exi_wait(drv_no);

	if(EXI_Select(drv_no,EXI_DEVICE_0,_ioCardFreq)==0) {
		EXI_Unlock(drv_no);
		return CARDIO_ERROR_NOCARD;
	}

	if(EXI_ImmEx(drv_no,ptr,1,EXI_READWRITE)==0) {
		EXI_Deselect(drv_no);
		EXI_Unlock(drv_no);
		return CARDIO_ERROR_IOERROR;
	}

	startT = gettick();
	while(*ptr&0x80) {
		*ptr = _ioClrFlag;
		if(EXI_ImmEx(drv_no,ptr,1,EXI_READWRITE)==0) {
			EXI_Deselect(drv_no);
			EXI_Unlock(drv_no);
			return CARDIO_ERROR_IOERROR;
		}
		if(!(*ptr&0x80)) break;
		if(__card_checktimeout(drv_no,startT,500)!=0) {
			*ptr = _ioClrFlag;
			if(EXI_ImmEx(drv_no,ptr,1,EXI_READWRITE)==0) {
				EXI_Deselect(drv_no);
				EXI_Unlock(drv_no);
				return CARDIO_ERROR_IOERROR;
			}
			if(*ptr&0x80) ret = CARDIO_ERROR_IOTIMEOUT;
			break;
		}
	}
	if(len>1 && ret==CARDIO_ERROR_READY) {
		*(++ptr) = _ioClrFlag;
		if(EXI_ImmEx(drv_no,ptr,len-1,EXI_READWRITE)==0) ret = CARDIO_ERROR_IOERROR;
	}

	EXI_Deselect(drv_no);
	EXI_Unlock(drv_no);
	return ret;
}