#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
struct TYPE_3__ {scalar_t__ rtc_at_update; int scale; int media_time_frac; int media_time; int /*<<< orphan*/  wall_time; } ;
typedef  TYPE_1__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 scalar_t__ vcos_getmicrosecs () ; 

__attribute__((used)) static void mmal_clock_update_local_time_locked(MMAL_CLOCK_PRIVATE_T *private)
{
   uint32_t time_now = vcos_getmicrosecs();
   uint32_t time_diff = (time_now > private->rtc_at_update) ? (time_now - private->rtc_at_update) : 0;

   private->wall_time += time_diff;

   /* For small clock scale values (i.e. slow motion), the media-time increment
    * could potentially be rounded down when doing lots of updates, so also keep
    * track of the fractional increment. */
   int64_t media_diff = ((int64_t)time_diff) * (int64_t)(private->scale << 8) + private->media_time_frac;

   private->media_time += media_diff >> 24;
   private->media_time_frac = media_diff & ((1<<24)-1);

   private->rtc_at_update = time_now;
}