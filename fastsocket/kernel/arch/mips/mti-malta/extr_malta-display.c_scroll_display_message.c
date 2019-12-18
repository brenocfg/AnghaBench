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
 scalar_t__ HZ ; 
 scalar_t__ display_count ; 
 int /*<<< orphan*/ * display_string ; 
 scalar_t__ jiffies ; 
 scalar_t__ max_display_count ; 
 int /*<<< orphan*/  mips_display_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_scroll_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void scroll_display_message(unsigned long data)
{
	mips_display_message(&display_string[display_count++]);
	if (display_count == max_display_count)
		display_count = 0;

	mod_timer(&mips_scroll_timer, jiffies + HZ);
}