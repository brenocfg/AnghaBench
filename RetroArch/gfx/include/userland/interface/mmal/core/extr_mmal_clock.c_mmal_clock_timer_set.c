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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  VCOS_UNSIGNED ;
typedef  int /*<<< orphan*/  RTOS_TIMER_TIME_T ;
typedef  int /*<<< orphan*/  MMAL_TIMER_T ;

/* Variables and functions */
 int /*<<< orphan*/  rtos_timer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_timer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mmal_clock_timer_set(MMAL_TIMER_T *timer, int64_t delay_us)
{
#ifdef USE_RTOS_TIMER
   rtos_timer_set(timer, (RTOS_TIMER_TIME_T)delay_us);
#else
   /* VCOS timer only provides millisecond accuracy */
   vcos_timer_set(timer, (VCOS_UNSIGNED)(delay_us / 1000));
#endif
}