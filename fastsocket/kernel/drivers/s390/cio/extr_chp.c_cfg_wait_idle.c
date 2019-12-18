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

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  cfg_busy ; 
 int /*<<< orphan*/  cfg_wait_queue ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cfg_wait_idle(void)
{
	if (wait_event_interruptible(cfg_wait_queue, !cfg_busy))
		return -ERESTARTSYS;
	return 0;
}