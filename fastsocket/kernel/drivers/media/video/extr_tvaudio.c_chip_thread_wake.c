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
struct CHIPSTATE {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void chip_thread_wake(unsigned long data)
{
	struct CHIPSTATE *chip = (struct CHIPSTATE*)data;
	wake_up_process(chip->thread);
}