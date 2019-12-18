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
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  w83697hf_deselect_wdt () ; 
 int /*<<< orphan*/  w83697hf_select_wdt () ; 
 int /*<<< orphan*/  w83697hf_set_reg (int,int) ; 
 int /*<<< orphan*/  w83697hf_write_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_enable(void)
{
	spin_lock(&io_lock);
	w83697hf_select_wdt();

	w83697hf_write_timeout(timeout);
	w83697hf_set_reg(0x30, 1);	/* Enable timer */

	w83697hf_deselect_wdt();
	spin_unlock(&io_lock);
}