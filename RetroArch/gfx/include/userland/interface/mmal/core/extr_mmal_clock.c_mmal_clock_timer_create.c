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
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  mmal_clock_timer_cb ; 
 scalar_t__ rtos_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ vcos_timer_create (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline MMAL_BOOL_T mmal_clock_timer_create(MMAL_TIMER_T *timer, void *ctx)
{
#ifdef USE_RTOS_TIMER
   return (rtos_timer_init(timer, mmal_clock_timer_cb, ctx) == 0);
#else
   return (vcos_timer_create(timer, "mmal-clock timer", mmal_clock_timer_cb, ctx) == VCOS_SUCCESS);
#endif
}