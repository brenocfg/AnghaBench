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
struct TYPE_7__ {int /*<<< orphan*/  request_threshold_enable; int /*<<< orphan*/  request_threshold; } ;
struct TYPE_6__ {int /*<<< orphan*/  threshold_enable; int /*<<< orphan*/  threshold; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_T ;
typedef  TYPE_1__ MMAL_CLOCK_REQUEST_THRESHOLD_T ;
typedef  TYPE_2__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  UNLOCK (TYPE_2__*) ; 

MMAL_STATUS_T mmal_clock_request_threshold_get(MMAL_CLOCK_T *clock, MMAL_CLOCK_REQUEST_THRESHOLD_T *req)
{
   MMAL_CLOCK_PRIVATE_T *private = (MMAL_CLOCK_PRIVATE_T *)clock;

   LOCK(private);
   req->threshold = private->request_threshold;
   req->threshold_enable = private->request_threshold_enable;
   UNLOCK(private);

   return MMAL_SUCCESS;
}