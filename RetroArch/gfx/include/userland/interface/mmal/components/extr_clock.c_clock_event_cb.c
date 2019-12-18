#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  component; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_CLOCK_EVENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  clock_event_queue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void clock_event_cb(MMAL_PORT_T *port, const MMAL_CLOCK_EVENT_T *event)
{
   clock_event_queue(port->component, port, event);
}