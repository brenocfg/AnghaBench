#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  request_threshold; } ;
struct TYPE_5__ {TYPE_1__ data; int /*<<< orphan*/  magic; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_REQUEST_THRESHOLD_T ;
typedef  TYPE_2__ MMAL_CLOCK_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_MAGIC ; 
 int /*<<< orphan*/  MMAL_CLOCK_EVENT_REQUEST_THRESHOLD ; 
 int /*<<< orphan*/  mmal_port_clock_forward_event (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static MMAL_STATUS_T mmal_port_clock_forward_request_threshold(MMAL_PORT_T *port,
      const MMAL_CLOCK_REQUEST_THRESHOLD_T *threshold)
{
   MMAL_CLOCK_EVENT_T event;

   event.id = MMAL_CLOCK_EVENT_REQUEST_THRESHOLD;
   event.magic = MMAL_CLOCK_EVENT_MAGIC;
   event.data.request_threshold = *threshold;

   return mmal_port_clock_forward_event(port, &event);
}