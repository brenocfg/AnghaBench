#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  prompt; } ;

/* Variables and functions */
 TYPE_1__* current_monitor ; 
 int /*<<< orphan*/  monitor_debug (char*) ; 
 int monitor_expect (int /*<<< orphan*/ ,char*,int) ; 

int
monitor_expect_prompt (char *buf, int buflen)
{
  monitor_debug ("MON Expecting prompt\n");
  return monitor_expect (current_monitor->prompt, buf, buflen);
}