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
 int /*<<< orphan*/  sh7750_ppc_reset () ; 
 int /*<<< orphan*/  sh7750_timer_notify ; 
 int /*<<< orphan*/  unregister_timer_hook (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh7750_ppc_exit(void)
{
	unregister_timer_hook(sh7750_timer_notify);

	sh7750_ppc_reset();
}