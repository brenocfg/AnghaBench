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
struct TYPE_7__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  threshold; } ;
struct TYPE_6__ {int /*<<< orphan*/  discont_duration; int /*<<< orphan*/  discont_threshold; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  TYPE_1__ MMAL_CLOCK_PRIVATE_T ;
typedef  TYPE_2__ MMAL_CLOCK_DISCONT_THRESHOLD_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  UNLOCK (TYPE_1__*) ; 

MMAL_STATUS_T mmal_clock_discont_threshold_get(MMAL_CLOCK_T *clock, MMAL_CLOCK_DISCONT_THRESHOLD_T *discont)
{
   MMAL_CLOCK_PRIVATE_T *private = (MMAL_CLOCK_PRIVATE_T *)clock;

   LOCK(private);
   discont->threshold = private->discont_threshold;
   discont->duration  = private->discont_duration;
   UNLOCK(private);

   return MMAL_SUCCESS;
}