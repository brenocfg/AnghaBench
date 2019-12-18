#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/ * list_free; int /*<<< orphan*/ * list_pending; } ;
struct TYPE_7__ {scalar_t__ media_time_at_timer; int /*<<< orphan*/  clock; TYPE_1__ request; } ;
struct TYPE_6__ {int /*<<< orphan*/  link; int /*<<< orphan*/  priv; int /*<<< orphan*/  cb_data; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_LIST_T ;
typedef  TYPE_2__ MMAL_CLOCK_REQUEST_T ;
typedef  TYPE_3__ MMAL_CLOCK_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 scalar_t__ mmal_list_pop_front (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_list_push_back (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_clock_request_flush_locked(MMAL_CLOCK_PRIVATE_T *private,
                                                     int64_t media_time)
{
   MMAL_LIST_T *pending = private->request.list_pending;
   MMAL_LIST_T *list_free = private->request.list_free;
   MMAL_CLOCK_REQUEST_T *request;

   while ((request = (MMAL_CLOCK_REQUEST_T *)mmal_list_pop_front(pending)) != NULL)
   {
      /* Inform the client */
      request->cb(&private->clock, media_time, request->cb_data, request->priv);
      /* Recycle request slot */
      mmal_list_push_back(list_free, &request->link);
   }

   private->media_time_at_timer = 0;

   return MMAL_SUCCESS;
}