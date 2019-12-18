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
 int /*<<< orphan*/  P32XI_HINT ; 
 int /*<<< orphan*/  p32x_schedule_hint (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  p32x_trigger_irq (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hint_event(unsigned int now)
{
  p32x_trigger_irq(NULL, now, P32XI_HINT);
  p32x_schedule_hint(NULL, now);
}