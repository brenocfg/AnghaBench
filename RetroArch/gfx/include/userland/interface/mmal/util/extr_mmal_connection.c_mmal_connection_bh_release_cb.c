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
struct TYPE_7__ {int /*<<< orphan*/  (* callback ) (TYPE_2__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ MMAL_POOL_T ;
typedef  TYPE_2__ MMAL_CONNECTION_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static MMAL_BOOL_T mmal_connection_bh_release_cb(MMAL_POOL_T *pool, MMAL_BUFFER_HEADER_T *buffer,
   void *userdata)
{
   MMAL_CONNECTION_T *connection = (MMAL_CONNECTION_T *)userdata;
   MMAL_PARAM_UNUSED(pool);

   /* Queue the buffer produced by the output port */
   mmal_queue_put(pool->queue, buffer);

   if (connection->callback)
      connection->callback(connection);

   return 0;
}