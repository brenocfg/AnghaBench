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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_clock_media_time_get_locked (int /*<<< orphan*/ *) ; 

int64_t mmal_clock_media_time_get(MMAL_CLOCK_T *clock)
{
   int64_t media_time;
   MMAL_CLOCK_PRIVATE_T *private = (MMAL_CLOCK_PRIVATE_T*)clock;

   LOCK(private);
   media_time = mmal_clock_media_time_get_locked(private);
   UNLOCK(private);

   return media_time;
}