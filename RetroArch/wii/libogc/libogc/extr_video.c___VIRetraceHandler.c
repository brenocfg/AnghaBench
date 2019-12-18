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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_ThreadBroadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_RefreshSamplingRate () ; 
 scalar_t__ VIDEO_GetCurrentTvMode () ; 
 scalar_t__ VI_EURGB60 ; 
 int /*<<< orphan*/  __VIGetCurrentPosition (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __VISetFilterEURGB60 (int) ; 
 scalar_t__ __VISetRegs () ; 
 int /*<<< orphan*/  __VISetYUVSEL (scalar_t__) ; 
 int* _viReg ; 
 scalar_t__ flushFlag ; 
 scalar_t__ oldDtvStatus ; 
 scalar_t__ oldTvStatus ; 
 int /*<<< orphan*/  positionCB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  postRetraceCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preRetraceCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retraceCount ; 
 int /*<<< orphan*/  video_queue ; 

__attribute__((used)) static void __VIRetraceHandler(u32 nIrq,void *pCtx)
{
#if defined(HW_RVL)
	u8 dtv, tv;
#endif
	u32 ret = 0;
	u32 intr;
	s32 xpos,ypos;

	intr = _viReg[24];
	if(intr&0x8000) {
		_viReg[24] = intr&~0x8000;
		ret |= 0x01;
	}

	intr = _viReg[26];
	if(intr&0x8000) {
		_viReg[26] = intr&~0x8000;
		ret |= 0x02;
	}

	intr = _viReg[28];
	if(intr&0x8000) {
		_viReg[28] = intr&~0x8000;
		ret |= 0x04;
	}

	intr = _viReg[30];
	if(intr&0x8000) {
		_viReg[30] = intr&~0x8000;
		ret |= 0x08;
	}

	intr = _viReg[30];
	if(ret&0x04 || ret&0x08) {
		if(positionCB!=NULL) {
			__VIGetCurrentPosition(&xpos,&ypos);
			positionCB(xpos,ypos);
		}
	}

	retraceCount++;
	if(preRetraceCB)
		preRetraceCB(retraceCount);

	if(flushFlag) {
		if(__VISetRegs()) {
			flushFlag = 0;
			SI_RefreshSamplingRate();
		}
	}
#if defined(HW_RVL)
	tv = VIDEO_GetCurrentTvMode();
	dtv = (_viReg[55]&0x01);
	if(dtv!=oldDtvStatus || tv!=oldTvStatus) __VISetYUVSEL(dtv);
	oldDtvStatus = dtv;

	if(tv!=oldTvStatus) {
		if(tv==VI_EURGB60) __VISetFilterEURGB60(1);
		else __VISetFilterEURGB60(0);
	}
	oldTvStatus = tv;
#endif
	if(postRetraceCB)
		postRetraceCB(retraceCount);

	LWP_ThreadBroadcast(video_queue);
}