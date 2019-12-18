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
typedef  int /*<<< orphan*/  MMAL_TIMER_T ;

/* Variables and functions */
 int /*<<< orphan*/  rtos_timer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_timer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mmal_clock_timer_cancel(MMAL_TIMER_T *timer)
{
#ifdef USE_RTOS_TIMER
   rtos_timer_cancel(timer);
#else
   vcos_timer_cancel(timer);
#endif
}