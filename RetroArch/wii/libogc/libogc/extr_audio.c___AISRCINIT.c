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
typedef  scalar_t__ u64 ;
typedef  int u32 ;

/* Variables and functions */
 int AI_AISFR ; 
 size_t AI_CONTROL ; 
 int AI_PSTAT ; 
 size_t AI_SAMPLE_COUNT ; 
 int AI_SCRESET ; 
 int* _aiReg ; 
 scalar_t__ bound_32KHz ; 
 scalar_t__ bound_48KHz ; 
 scalar_t__ buffer ; 
 scalar_t__ diff_ticks (scalar_t__,scalar_t__) ; 
 scalar_t__ gettime () ; 
 scalar_t__ max_wait ; 
 scalar_t__ min_wait ; 

__attribute__((used)) static void __AISRCINIT()
{
	int done = 0;
	u32 sample_counter;
	u64 time1, time2, tdiff;
	u64 wait = 0;

	while (!done) {
		_aiReg[AI_CONTROL] |=  AI_SCRESET;
		_aiReg[AI_CONTROL] &= ~AI_AISFR;
		_aiReg[AI_CONTROL] |=  AI_PSTAT;

#ifdef HW_DOL
		sample_counter = _aiReg[AI_SAMPLE_COUNT];
		while (sample_counter == _aiReg[AI_SAMPLE_COUNT]) {}
#else
		sample_counter = _aiReg[AI_SAMPLE_COUNT] & 0x7fffffff;
		while (sample_counter == (_aiReg[AI_SAMPLE_COUNT] & 0x7fffffff)) {}
#endif

		time1 = gettime();

		_aiReg[AI_CONTROL] |= AI_AISFR;
		_aiReg[AI_CONTROL] |= AI_PSTAT;

#ifdef HW_DOL
		sample_counter = _aiReg[AI_SAMPLE_COUNT];
		while (sample_counter == _aiReg[AI_SAMPLE_COUNT]) {}
#else
		sample_counter = _aiReg[AI_SAMPLE_COUNT] & 0x7fffffff;
		while (sample_counter == (_aiReg[AI_SAMPLE_COUNT] & 0x7fffffff)) {}
#endif

		time2 = gettime();
		tdiff = time2 - time1;

		_aiReg[AI_CONTROL] &= ~AI_AISFR;
		_aiReg[AI_CONTROL] &= ~AI_PSTAT;

		if ((tdiff > (bound_32KHz - buffer)) &&
			(tdiff < (bound_32KHz + buffer))) {
			if (tdiff < (bound_48KHz - buffer)) {
				wait = max_wait;
				done = 1;
			}
		} else {
			wait = min_wait;
			done = 1;
		}
	}

	while (diff_ticks(time2, gettime()) < wait) {}
}