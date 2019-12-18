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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_ThreadSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 scalar_t__ retraceCount ; 
 int /*<<< orphan*/  video_queue ; 

void VIDEO_WaitVSync(void)
{
	u32 level;
	u32 retcnt;

	_CPU_ISR_Disable(level);
	retcnt = retraceCount;
	do {
		LWP_ThreadSleep(video_queue);
	} while(retraceCount==retcnt);
	_CPU_ISR_Restore(level);
}