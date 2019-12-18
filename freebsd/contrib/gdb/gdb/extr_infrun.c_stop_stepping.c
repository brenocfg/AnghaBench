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
struct execution_control_state {scalar_t__ wait_some_more; } ;

/* Variables and functions */

__attribute__((used)) static void
stop_stepping (struct execution_control_state *ecs)
{
  /* Let callers know we don't want to wait for the inferior anymore.  */
  ecs->wait_some_more = 0;
}