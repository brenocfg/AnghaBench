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
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  scalar_t__ MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_clock_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_clock_stop (int /*<<< orphan*/ *) ; 

MMAL_STATUS_T mmal_clock_active_set(MMAL_CLOCK_T *clock, MMAL_BOOL_T active)
{
   if (active)
      mmal_clock_start(clock);
   else
      mmal_clock_stop(clock);

   return MMAL_SUCCESS;
}