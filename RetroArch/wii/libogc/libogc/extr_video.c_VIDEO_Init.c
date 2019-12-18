#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int nonInter; int tv; int dispSizeX; int dispSizeY; int dispPosX; int fbSizeX; int fbSizeY; int panSizeX; int panSizeY; int wordPerLine; int std; int wpl; int black; scalar_t__ rtfbb; scalar_t__ rbfbb; scalar_t__ tfbb; scalar_t__ bfbb; scalar_t__ threeD; scalar_t__ xof; int /*<<< orphan*/  fbMode; scalar_t__ panPosY; scalar_t__ panPosX; scalar_t__ dispPosY; TYPE_1__* timing; } ;
struct TYPE_4__ {int acv; } ;

/* Variables and functions */
 TYPE_3__ HorVer ; 
 int /*<<< orphan*/  IRQMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_PI_VI ; 
 int /*<<< orphan*/  IRQ_Request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int VI_DEBUG ; 
 int VI_MAX_WIDTH_NTSC ; 
 int /*<<< orphan*/  VI_TVMODE_NTSC_INT ; 
 int /*<<< orphan*/  VI_XFBMODE_SF ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int _SHIFTL (int,int,int) ; 
 void* _SHIFTR (int,int,int) ; 
 int /*<<< orphan*/  __UnmaskIrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __VIInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __VIRetraceHandler ; 
 int /*<<< orphan*/  __VISetupEncoder () ; 
 int /*<<< orphan*/  __adjustPosition (int) ; 
 TYPE_1__* __gettiming (int) ; 
 int /*<<< orphan*/  __importAdjustingValues () ; 
 int* _viReg ; 
 scalar_t__ changed ; 
 TYPE_1__* currTiming ; 
 int currTvMode ; 
 scalar_t__ flushFlag ; 
 int /*<<< orphan*/ * postRetraceCB ; 
 int /*<<< orphan*/ * preRetraceCB ; 
 int* regs ; 
 scalar_t__ retraceCount ; 
 scalar_t__ shdw_changeMode ; 
 scalar_t__ shdw_changed ; 
 int* taps ; 
 int /*<<< orphan*/  video_queue ; 

void VIDEO_Init()
{
	u32 level,vimode = 0;

	_CPU_ISR_Disable(level);

	if(!(_viReg[1]&0x0001))
		__VIInit(VI_TVMODE_NTSC_INT);

	retraceCount = 0;
	changed = 0;
	shdw_changed = 0;
	shdw_changeMode = 0;
	flushFlag = 0;

	_viReg[38] = ((taps[1]>>6)|(taps[2]<<4));
	_viReg[39] = (taps[0]|_SHIFTL(taps[1],10,6));
	_viReg[40] = ((taps[4]>>6)|(taps[5]<<4));
	_viReg[41] = (taps[3]|_SHIFTL(taps[4],10,6));
	_viReg[42] = ((taps[7]>>6)|(taps[8]<<4));
	_viReg[43] = (taps[6]|_SHIFTL(taps[7],10,6));
	_viReg[44] = (taps[11]|(taps[12]<<8));
	_viReg[45] = (taps[9]|(taps[10]<<8));
	_viReg[46] = (taps[15]|(taps[16]<<8));
	_viReg[47] = (taps[13]|(taps[14]<<8));
	_viReg[48] = (taps[19]|(taps[20]<<8));
	_viReg[49] = (taps[17]|(taps[18]<<8));
	_viReg[50] = (taps[23]|(taps[24]<<8));
	_viReg[51] = (taps[21]|(taps[22]<<8));
	_viReg[56] = 640;

	__importAdjustingValues();

	HorVer.nonInter = _SHIFTR(_viReg[1],2,1);
	HorVer.tv = _SHIFTR(_viReg[1],8,2);

	vimode = HorVer.nonInter;
	if(HorVer.tv!=VI_DEBUG) vimode += (HorVer.tv<<2);
	currTiming = __gettiming(vimode);
	currTvMode = HorVer.tv;

	regs[1] = _viReg[1];
	HorVer.timing = currTiming;
	HorVer.dispSizeX = 640;
	HorVer.dispSizeY = currTiming->acv<<1;
	HorVer.dispPosX = (VI_MAX_WIDTH_NTSC-HorVer.dispSizeX)/2;
	HorVer.dispPosY = 0;

	__adjustPosition(currTiming->acv);

	HorVer.fbSizeX = 640;
	HorVer.fbSizeY = currTiming->acv<<1;
	HorVer.panPosX = 0;
	HorVer.panPosY = 0;
	HorVer.panSizeX = 640;
	HorVer.panSizeY = currTiming->acv<<1;
	HorVer.fbMode = VI_XFBMODE_SF;
	HorVer.wordPerLine = 40;
	HorVer.std = 40;
	HorVer.wpl = 40;
	HorVer.xof = 0;
	HorVer.black = 1;
	HorVer.threeD = 0;
	HorVer.bfbb = 0;
	HorVer.tfbb = 0;
	HorVer.rbfbb = 0;
	HorVer.rtfbb = 0;

	_viReg[24] &= ~0x8000;
	_viReg[26] &= ~0x8000;

	preRetraceCB = NULL;
	postRetraceCB = NULL;

	LWP_InitQueue(&video_queue);

	IRQ_Request(IRQ_PI_VI,__VIRetraceHandler,NULL);
	__UnmaskIrq(IRQMASK(IRQ_PI_VI));
#if defined(HW_RVL)
	__VISetupEncoder();
#endif
	_CPU_ISR_Restore(level);
}