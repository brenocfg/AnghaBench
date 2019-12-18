#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int s8 ;
struct TYPE_3__ {int stickX; int stickY; int substickX; int substickY; int triggerL; int triggerR; int analogA; int analogB; int /*<<< orphan*/  button; } ;
typedef  TYPE_1__ PADStatus ;

/* Variables and functions */
 int /*<<< orphan*/  _SHIFTR (int,int,int) ; 
 int __pad_analogmode ; 
 void* __pad_clampS8 (int,int /*<<< orphan*/ ) ; 
 void* __pad_clampU8 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** __pad_origin ; 

__attribute__((used)) static void SPEC2_MakeStatus(u32 chan,u32 *data,PADStatus *status)
{
	u32 mode;

	status->button = _SHIFTR(data[0],16,14);

	status->stickX = (s8)(data[0]>>8);
	status->stickY = (s8)data[0];
	mode = __pad_analogmode&0x0700;
	if(mode==0x100) {
		status->substickX = (s8)((data[1]>>24)&0xf0);
		status->substickY = (s8)((data[1]>>8)&0xff);
		status->triggerL = (u8)((data[1]>>16)&0xff);
		status->triggerR = (u8)((data[1]>>8)&0xff);
		status->analogA = (u8)(data[1]&0xf0);
		status->analogB = (u8)((data[1]<<4)&0xf0);
	} else if(mode==0x200) {
		status->substickX = (s8)((data[1]>>24)&0xf0);
		status->substickY = (s8)((data[1]>>20)&0xf0);
		status->triggerL = (u8)((data[1]>>16)&0xf0);
		status->triggerR = (u8)((data[1]>>12)&0xf0);
		status->analogA = (u8)((data[1]>>8)&0xff);
		status->analogB = (s8)data[1]&0xff;
	} else if(mode==0x300) {
		status->substickX = (s8)((data[1]>>24)&0xff);
		status->substickY = (s8)((data[1]>>16)&0xff);
		status->triggerL = (u8)((data[1]>>8)&0xff);
		status->triggerR = (u8)data[1]&0xff;
		status->analogA = 0;
		status->analogB = 0;
	} else if(mode==0x400) {
		status->substickX = (s8)((data[1]>>24)&0xff);
		status->substickY = (s8)((data[1]>>16)&0xff);
		status->triggerL = 0;
		status->triggerR = 0;
		status->analogA = (u8)((data[1]>>8)&0xff);
		status->analogB = (u8)data[1]&0xff ;
	} else if(!mode || mode==0x500 || mode==0x600 || mode==0x700) {
		status->substickX = (s8)((data[1]>>24)&0xff);
		status->substickY = (s8)((data[1]>>16)&0xff);
		status->triggerL = (u8)((data[1]>>8)&0xf0);
		status->triggerR = (u8)((data[1]>>4)&0xf0);
		status->analogA = (u8)(data[1]&0xf0);
		status->analogB = (u8)((data[1]<<4)&0xf0);
	}

	status->stickX -= 128;
	status->stickY -= 128;
	status->substickX -= 128;
	status->substickY -= 128;
	status->stickX = __pad_clampS8(status->stickX,__pad_origin[chan][2]);
	status->stickY = __pad_clampS8(status->stickY,__pad_origin[chan][3]);
	status->substickX = __pad_clampS8(status->substickX,__pad_origin[chan][4]);
	status->substickY = __pad_clampS8(status->substickY,__pad_origin[chan][5]);
	status->triggerL = __pad_clampU8(status->triggerL,__pad_origin[chan][6]);
	status->triggerR = __pad_clampU8(status->triggerR,__pad_origin[chan][7]);
}