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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ CARDIO_ERROR_IOERROR ; 
 scalar_t__ CARDIO_ERROR_NOCARD ; 
 scalar_t__ CARDIO_ERROR_READY ; 
 int /*<<< orphan*/  EXI_DEVICE_0 ; 
 int /*<<< orphan*/  EXI_Deselect (scalar_t__) ; 
 scalar_t__ EXI_ImmEx (scalar_t__,int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ EXI_Select (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EXI_SelectSD (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXI_Unlock (scalar_t__) ; 
 int /*<<< orphan*/  EXI_WRITE ; 
 scalar_t__ MAX_DRIVE ; 
 int /*<<< orphan*/  __exi_wait (scalar_t__) ; 
 int __make_crc7 (int*,int) ; 
 int /*<<< orphan*/  _ioCardFreq ; 
 int _ioClrFlag ; 
 scalar_t__ _ioWPFlag ; 

__attribute__((used)) static s32 __card_writecmd0(s32 drv_no)
{
	u8 crc;
	u32 cnt;
	u8 dummy[128];
	u8 cmd[5] = {0,0,0,0,0};

	if(drv_no<0 || drv_no>=MAX_DRIVE) return CARDIO_ERROR_NOCARD;

	_ioClrFlag = 0xff;
	cmd[0] = 0x40;
	crc = __make_crc7(cmd,5);

	if(_ioWPFlag) {
		_ioClrFlag = 0x00;
		for(cnt=0;cnt<5;cnt++) cmd[cnt] ^= -1;
	}

	for(cnt=0;cnt<128;cnt++) dummy[cnt] = _ioClrFlag;

	__exi_wait(drv_no);

	if(EXI_SelectSD(drv_no,EXI_DEVICE_0,_ioCardFreq)==0) {
		EXI_Unlock(drv_no);
		return CARDIO_ERROR_NOCARD;
	}

	cnt = 0;
	while(cnt<20) {
		if(EXI_ImmEx(drv_no,dummy,128,EXI_WRITE)==0) {
			EXI_Deselect(drv_no);
			EXI_Unlock(drv_no);
			return CARDIO_ERROR_IOERROR;
		}
		cnt++;
	}
	EXI_Deselect(drv_no);

	if(EXI_Select(drv_no,EXI_DEVICE_0,_ioCardFreq)==0) {
		EXI_Unlock(drv_no);
		return CARDIO_ERROR_NOCARD;
	}

	crc |= 0x01;
	if(_ioWPFlag) crc ^= -1;
	if(EXI_ImmEx(drv_no,cmd,5,EXI_WRITE)==0) {
		EXI_Deselect(drv_no);
		EXI_Unlock(drv_no);
		return CARDIO_ERROR_IOERROR;
	}

	if(EXI_ImmEx(drv_no,&crc,1,EXI_WRITE)==0) {
		EXI_Deselect(drv_no);
		EXI_Unlock(drv_no);
		return CARDIO_ERROR_IOERROR;
	}

	EXI_Deselect(drv_no);
	EXI_Unlock(drv_no);
	return CARDIO_ERROR_READY;
}