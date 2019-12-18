#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ MMAL_CONNECTION_T ;
typedef  TYPE_2__ MMAL_CONNECTION_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

void mmal_connection_acquire(MMAL_CONNECTION_T *connection)
{
   MMAL_CONNECTION_PRIVATE_T *private = (MMAL_CONNECTION_PRIVATE_T *)connection;
   LOG_TRACE("connection %s(%p), refcount %i", connection->name, connection,
             private->refcount);
   private->refcount++;
}