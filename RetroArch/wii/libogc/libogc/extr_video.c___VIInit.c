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
struct _timing {int hcs; int hce; int hlw; int hbs640; int hbe640; int hsy; int equ; int psbOdd; int prbOdd; int acv; int psbEven; int prbEven; int be3; int bs3; int be1; int bs1; int be4; int bs4; int be2; int bs2; int nhlines; } ;

/* Variables and functions */
 int VI_DEBUG_PAL ; 
 int VI_NTSC ; 
 int VI_PAL ; 
 struct _timing* __gettiming (int) ; 
 int* _viReg ; 

__attribute__((used)) static void __VIInit(u32 vimode)
{
	u32 cnt;
	u32 vi_mode,interlace,progressive;
	const struct _timing *cur_timing = NULL;

	vi_mode = ((vimode>>2)&0x07);
	interlace = (vimode&0x01);
	progressive = (vimode&0x02);

	cur_timing = __gettiming(vimode);

	//reset the interface
	cnt = 0;
	_viReg[1] = 0x02;
	while(cnt<1000) cnt++;
	_viReg[1] = 0x00;

	// now begin to setup the interface
	_viReg[2] = ((cur_timing->hcs<<8)|cur_timing->hce);		//set HCS & HCE
	_viReg[3] = cur_timing->hlw;							//set Half Line Width

	_viReg[4] = (cur_timing->hbs640<<1);					//set HBS640
	_viReg[5] = ((cur_timing->hbe640<<7)|cur_timing->hsy);	//set HBE640 & HSY

	_viReg[0] = cur_timing->equ;

	_viReg[6] = (cur_timing->psbOdd+2);							//set PSB odd field
	_viReg[7] = (cur_timing->prbOdd+((cur_timing->acv<<1)-2));	//set PRB odd field

	_viReg[8] = (cur_timing->psbEven+2);						//set PSB even field
	_viReg[9] = (cur_timing->prbEven+((cur_timing->acv<<1)-2));	//set PRB even field

	_viReg[10] = ((cur_timing->be3<<5)|cur_timing->bs3);		//set BE3 & BS3
	_viReg[11] = ((cur_timing->be1<<5)|cur_timing->bs1);		//set BE1 & BS1

	_viReg[12] = ((cur_timing->be4<<5)|cur_timing->bs4);		//set BE4 & BS4
	_viReg[13] = ((cur_timing->be2<<5)|cur_timing->bs2);		//set BE2 & BS2

	_viReg[24] = (0x1000|((cur_timing->nhlines/2)+1));
	_viReg[25] = (cur_timing->hlw+1);

	_viReg[26] = 0x1001;		//set DI1
	_viReg[27] = 0x0001;		//set DI1
	_viReg[36] = 0x2828;		//set HSR

	if(vi_mode<VI_PAL && vi_mode>=VI_DEBUG_PAL) vi_mode = VI_NTSC;
	if(progressive){
		_viReg[1] = ((vi_mode<<8)|0x0005);		//set MODE & INT & enable
		_viReg[54] = 0x0001;
	} else {
		_viReg[1] = ((vi_mode<<8)|(interlace<<2)|0x0001);
		_viReg[54] = 0x0000;
	}
}