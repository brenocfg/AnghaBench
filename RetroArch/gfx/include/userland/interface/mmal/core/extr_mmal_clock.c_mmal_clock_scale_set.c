#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  long long int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_10__ {scalar_t__ scale_inv; scalar_t__ scale; TYPE_1__ scale_rational; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  TYPE_2__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ Q16_ONE ; 
 int /*<<< orphan*/  UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_clock_update_local_time_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_clock_wake_thread (TYPE_2__*) ; 
 scalar_t__ mmal_rational_to_fixed_16_16 (TYPE_1__) ; 

MMAL_STATUS_T mmal_clock_scale_set(MMAL_CLOCK_T *clock, MMAL_RATIONAL_T scale)
{
   MMAL_CLOCK_PRIVATE_T *private = (MMAL_CLOCK_PRIVATE_T*)clock;

   LOG_TRACE("new scale %d/%d", scale.num, scale.den);

   LOCK(private);

   mmal_clock_update_local_time_locked(private);

   private->scale_rational = scale;
   private->scale = mmal_rational_to_fixed_16_16(scale);

   if (private->scale)
      private->scale_inv = (int32_t)((1LL << 32) / (int64_t)private->scale);
   else
      private->scale_inv = Q16_ONE; /* clock is paused */

   UNLOCK(private);

   mmal_clock_wake_thread(private);

   return MMAL_SUCCESS;
}