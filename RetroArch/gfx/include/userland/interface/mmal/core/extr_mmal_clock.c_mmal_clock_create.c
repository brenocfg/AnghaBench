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
struct TYPE_7__ {int /*<<< orphan*/  clock; int /*<<< orphan*/  request_threshold_enable; scalar_t__ request_threshold; int /*<<< orphan*/  discont_duration; int /*<<< orphan*/  discont_threshold; int /*<<< orphan*/  update_threshold_upper; int /*<<< orphan*/  update_threshold_lower; int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int member_0; int member_1; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  TYPE_2__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DISCONT_DURATION ; 
 int /*<<< orphan*/  CLOCK_DISCONT_THRESHOLD ; 
 int /*<<< orphan*/  CLOCK_UPDATE_THRESHOLD_LOWER ; 
 int /*<<< orphan*/  CLOCK_UPDATE_THRESHOLD_UPPER ; 
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  mmal_clock_scale_set (int /*<<< orphan*/ *,TYPE_1__) ; 
 TYPE_2__* vcos_calloc (int,unsigned int,char*) ; 
 int /*<<< orphan*/  vcos_free (TYPE_2__*) ; 
 scalar_t__ vcos_mutex_create (int /*<<< orphan*/ *,char*) ; 

MMAL_STATUS_T mmal_clock_create(MMAL_CLOCK_T **clock)
{
   unsigned int size = sizeof(MMAL_CLOCK_PRIVATE_T);
   MMAL_RATIONAL_T scale = { 1, 1 };
   MMAL_CLOCK_PRIVATE_T *private;

   /* Sanity checking */
   if (clock == NULL)
      return MMAL_EINVAL;

   private = vcos_calloc(1, size, "mmal-clock");
   if (!private)
   {
      LOG_ERROR("failed to allocate memory");
      return MMAL_ENOMEM;
   }

   if (vcos_mutex_create(&private->lock, "mmal-clock lock") != VCOS_SUCCESS)
   {
      LOG_ERROR("failed to create lock mutex");
      vcos_free(private);
      return MMAL_ENOSPC;
   }

   /* Set the default threshold values */
   private->update_threshold_lower = CLOCK_UPDATE_THRESHOLD_LOWER;
   private->update_threshold_upper = CLOCK_UPDATE_THRESHOLD_UPPER;
   private->discont_threshold      = CLOCK_DISCONT_THRESHOLD;
   private->discont_duration       = CLOCK_DISCONT_DURATION;
   private->request_threshold      = 0;
   private->request_threshold_enable = MMAL_FALSE;

   /* Default scale = 1.0, i.e. normal playback speed */
   mmal_clock_scale_set(&private->clock, scale);

   *clock = &private->clock;
   return MMAL_SUCCESS;
}