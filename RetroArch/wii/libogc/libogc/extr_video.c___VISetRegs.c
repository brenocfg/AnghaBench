#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/  tv; int /*<<< orphan*/  timing; } ;

/* Variables and functions */
 TYPE_1__ HorVer ; 
 int VI_REGCHANGE (size_t) ; 
 int /*<<< orphan*/  __getCurrentFieldEvenOdd () ; 
 int /*<<< orphan*/ * _viReg ; 
 size_t cntlzd (int) ; 
 int /*<<< orphan*/  currTiming ; 
 int /*<<< orphan*/  currTvMode ; 
 int /*<<< orphan*/  currentFb ; 
 int /*<<< orphan*/  nextFb ; 
 int shdw_changeMode ; 
 int shdw_changed ; 
 int /*<<< orphan*/ * shdw_regs ; 

__attribute__((used)) static inline u32 __VISetRegs()
{
	u32 val;
	u64 mask;

	if(shdw_changeMode==1){
		if(!__getCurrentFieldEvenOdd()) return 0;
	}

	while(shdw_changed) {
		val = cntlzd(shdw_changed);
		_viReg[val] = shdw_regs[val];
		mask = VI_REGCHANGE(val);
		shdw_changed &= ~mask;
	}
	shdw_changeMode = 0;
	currTiming = HorVer.timing;
	currTvMode = HorVer.tv;

	currentFb = nextFb;

	return 1;
}