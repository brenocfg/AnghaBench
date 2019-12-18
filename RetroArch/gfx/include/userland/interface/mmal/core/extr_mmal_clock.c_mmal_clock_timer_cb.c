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
typedef  int /*<<< orphan*/  MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_clock_wake_thread (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmal_clock_timer_cb(void *ctx)
{
   /* Notify the worker thread */
   mmal_clock_wake_thread((MMAL_CLOCK_PRIVATE_T*)ctx);
}