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
struct TYPE_2__ {int* need_draw; scalar_t__* draw_finished; } ;

/* Variables and functions */
 scalar_t__ YAB_THREAD_VIDSOFT_PRIORITY_0 ; 
 int /*<<< orphan*/  YabThreadWake (scalar_t__) ; 
 TYPE_1__ priority_thread_context ; 

void TitanStartPriorityThread(int which)
{
   priority_thread_context.need_draw[which] = 1;
   priority_thread_context.draw_finished[which] = 0;
   YabThreadWake(YAB_THREAD_VIDSOFT_PRIORITY_0 + which);
}