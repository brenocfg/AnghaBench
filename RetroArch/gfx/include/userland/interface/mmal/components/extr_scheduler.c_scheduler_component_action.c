#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;

/* Variables and functions */
 scalar_t__ scheduler_component_process_buffers (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scheduler_component_action(MMAL_COMPONENT_T *component)
{
   /* Send requests to the clock */
   while (scheduler_component_process_buffers(component));
}