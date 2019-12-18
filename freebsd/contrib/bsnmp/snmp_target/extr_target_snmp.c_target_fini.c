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
 int /*<<< orphan*/  or_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_notification ; 
 int /*<<< orphan*/  reg_target ; 
 int /*<<< orphan*/  target_flush_all () ; 

__attribute__((used)) static int
target_fini(void)
{
	target_flush_all();
	or_unregister(reg_target);
	or_unregister(reg_notification);

	return (0);
}