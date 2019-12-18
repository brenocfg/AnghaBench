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
typedef  int u32 ;

/* Variables and functions */
 int VIDEO_GetCurrentTvMode () ; 
 int VI_NTSC ; 
 int* _viReg ; 
 int sys_fontenc ; 

u32 SYS_GetFontEncoding()
{
	u32 ret,tv_mode;

	if(sys_fontenc<=0x0001) return sys_fontenc;

	ret = 0;
	tv_mode = VIDEO_GetCurrentTvMode();
	if(tv_mode==VI_NTSC && _viReg[55]&0x0002) ret = 1;
	sys_fontenc = ret;
	return ret;
}