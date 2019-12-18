#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  update_threshold_upper; int /*<<< orphan*/  update_threshold_lower; } ;
struct TYPE_6__ {int /*<<< orphan*/  threshold_upper; int /*<<< orphan*/  threshold_lower; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_CLOCK_UPDATE_THRESHOLD_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  TYPE_2__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  UNLOCK (TYPE_2__*) ; 

MMAL_STATUS_T mmal_clock_update_threshold_get(MMAL_CLOCK_T *clock, MMAL_CLOCK_UPDATE_THRESHOLD_T *update_threshold)
{
   MMAL_CLOCK_PRIVATE_T *private = (MMAL_CLOCK_PRIVATE_T *)clock;

   LOCK(private);
   update_threshold->threshold_lower = private->update_threshold_lower;
   update_threshold->threshold_upper = private->update_threshold_upper;
   UNLOCK(private);

   return MMAL_SUCCESS;
}