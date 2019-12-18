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
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w83697hf_deselect_wdt () ; 
 unsigned char w83697hf_get_reg (int) ; 
 int /*<<< orphan*/  w83697hf_select_wdt () ; 

__attribute__((used)) static unsigned char wdt_running(void)
{
	unsigned char t;

	spin_lock(&io_lock);
	w83697hf_select_wdt();

	t = w83697hf_get_reg(0xF4);	/* Read timer */

	w83697hf_deselect_wdt();
	spin_unlock(&io_lock);

	return t;
}