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
struct TYPE_7__ {int /*<<< orphan*/  (* callback ) (TYPE_3__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {TYPE_3__ wrapper; int /*<<< orphan*/  sema; } ;
typedef  TYPE_1__ MMAL_WRAPPER_PRIVATE_T ;
typedef  TYPE_2__ MMAL_POOL_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_BOOL_T mmal_wrapper_bh_release_cb(MMAL_POOL_T *pool, MMAL_BUFFER_HEADER_T *buffer,
   void *userdata)
{
   MMAL_WRAPPER_PRIVATE_T *private = (MMAL_WRAPPER_PRIVATE_T *)userdata;

   mmal_queue_put(pool->queue, buffer);
   vcos_semaphore_post(&private->sema);

   if (private->wrapper.callback)
      private->wrapper.callback(&private->wrapper);

   return 0;
}