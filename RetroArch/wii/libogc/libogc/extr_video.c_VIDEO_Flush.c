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
struct TYPE_2__ {int /*<<< orphan*/  bufAddr; } ;

/* Variables and functions */
 TYPE_1__ HorVer ; 
 int VI_REGCHANGE (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (size_t) ; 
 int /*<<< orphan*/  changeMode ; 
 int changed ; 
 size_t cntlzd (int) ; 
 int flushFlag ; 
 int /*<<< orphan*/  nextFb ; 
 int /*<<< orphan*/ * regs ; 
 int /*<<< orphan*/  shdw_changeMode ; 
 int shdw_changed ; 
 int /*<<< orphan*/ * shdw_regs ; 

void VIDEO_Flush()
{
	u32 level;
	u32 val;
	u64 mask;

	_CPU_ISR_Disable(level);
	shdw_changeMode |= changeMode;
	changeMode = 0;

	shdw_changed |= changed;
	while(changed) {
		val = cntlzd(changed);
		shdw_regs[val] = regs[val];
		mask = VI_REGCHANGE(val);
		changed &= ~mask;
	}
	flushFlag = 1;
	nextFb = HorVer.bufAddr;
	_CPU_ISR_Restore(level);
}