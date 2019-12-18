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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {scalar_t__ user_data; } ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  int /*<<< orphan*/  (* MMAL_PORT_CLOCK_REQUEST_CB ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_VOID_FP ;
typedef  TYPE_1__ MMAL_CLOCK_T ;

/* Variables and functions */

__attribute__((used)) static void mmal_port_clock_request_cb(MMAL_CLOCK_T* clock, int64_t media_time, void *cb_data, MMAL_CLOCK_VOID_FP cb)
{
   MMAL_PORT_CLOCK_REQUEST_CB cb_client = (MMAL_PORT_CLOCK_REQUEST_CB)cb;

   /* Forward to the client */
   cb_client((MMAL_PORT_T*)clock->user_data, media_time, cb_data);
}