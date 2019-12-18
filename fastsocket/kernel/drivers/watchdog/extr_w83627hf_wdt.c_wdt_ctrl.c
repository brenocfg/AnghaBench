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
 int /*<<< orphan*/  WDT_EFDR ; 
 int /*<<< orphan*/  WDT_EFER ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  w83627hf_select_wd_register () ; 
 int /*<<< orphan*/  w83627hf_unselect_wd_register () ; 

__attribute__((used)) static void wdt_ctrl(int timeout)
{
	spin_lock(&io_lock);

	w83627hf_select_wd_register();

	outb_p(0xF6, WDT_EFER);    /* Select CRF6 */
	outb_p(timeout, WDT_EFDR); /* Write Timeout counter to CRF6 */

	w83627hf_unselect_wd_register();

	spin_unlock(&io_lock);
}