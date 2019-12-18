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
struct TYPE_4__ {int /*<<< orphan*/ * function; scalar_t__ data; scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ INPUT_POLL_TIME ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  panel_scan_timer ; 
 TYPE_1__ scan_timer ; 

__attribute__((used)) static void init_scan_timer(void)
{
	if (scan_timer.function != NULL)
		return;		/* already started */

	init_timer(&scan_timer);
	scan_timer.expires = jiffies + INPUT_POLL_TIME;
	scan_timer.data = 0;
	scan_timer.function = (void *)&panel_scan_timer;
	add_timer(&scan_timer);
}