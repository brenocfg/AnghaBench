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
struct _xy {int line; int /*<<< orphan*/  cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI_SetXY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 struct _xy* __si_getxy () ; 
 int* _viReg ; 
 int sampling_rate ; 

void SI_SetSamplingRate(u32 samplingrate)
{
	u32 div,level;
	struct _xy *xy = NULL;

	if(samplingrate>11) samplingrate = 11;

	_CPU_ISR_Disable(level);
	sampling_rate = samplingrate;
	xy = __si_getxy();

	div = 1;
	if(_viReg[54]&0x0001) div = 2;

	SI_SetXY(div*xy[samplingrate].line,xy[samplingrate].cnt);
	_CPU_ISR_Restore(level);
}