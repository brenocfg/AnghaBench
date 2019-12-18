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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {scalar_t__ threeD; int /*<<< orphan*/  rbfbb; int /*<<< orphan*/  rtfbb; int /*<<< orphan*/  bfbb; int /*<<< orphan*/  tfbb; void* bufAddr; } ;

/* Variables and functions */
 TYPE_1__ HorVer ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __setFbbRegs (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _viReg ; 
 int fbSet ; 
 int /*<<< orphan*/ * regs ; 

void VIDEO_SetFramebuffer(void *fb)
{
	u32 level;

	_CPU_ISR_Disable(level);
	fbSet = 1;
	HorVer.bufAddr = fb;
	__setFbbRegs(&HorVer,&HorVer.tfbb,&HorVer.bfbb,&HorVer.rtfbb,&HorVer.rbfbb);
	_viReg[14] = regs[14];
	_viReg[15] = regs[15];

	_viReg[18] = regs[18];
	_viReg[19] = regs[19];

	if(HorVer.threeD) {
		_viReg[16] = regs[16];
		_viReg[17] = regs[17];

		_viReg[20] = regs[20];
		_viReg[21] = regs[21];
	}
	_CPU_ISR_Restore(level);
}