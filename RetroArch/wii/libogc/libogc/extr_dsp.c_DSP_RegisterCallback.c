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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ DSPCallback ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 scalar_t__ __dsp_def_taskcb ; 
 scalar_t__ __dsp_intcb ; 

DSPCallback DSP_RegisterCallback(DSPCallback usr_cb)
{
	u32 level;
	DSPCallback ret;
	_CPU_ISR_Disable(level);
	ret = __dsp_intcb;
	if(usr_cb)
		__dsp_intcb = usr_cb;
	else
		__dsp_intcb = __dsp_def_taskcb;
	_CPU_ISR_Restore(level);

	return ret;
}