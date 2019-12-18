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
 int /*<<< orphan*/  seq_reset () ; 

__attribute__((used)) static void seq_panic(void)
{
	/*
	 * This routine is called by the application in case the user
	 * wants to reset the system to the default state.
	 */

	seq_reset();

	/*
	 * Since some of the devices don't recognize the active sensing and
	 * all notes off messages, we have to shut all notes manually.
	 *
	 *      TO BE IMPLEMENTED LATER
	 */

	/*
	 * Also return the controllers to their default states
	 */
}