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
 int /*<<< orphan*/  pc87413_enable_sw_wd_tren (unsigned int) ; 
 int /*<<< orphan*/  pc87413_enable_sw_wd_trg (unsigned int) ; 
 int /*<<< orphan*/  pc87413_enable_swc () ; 
 int /*<<< orphan*/  pc87413_enable_wden (unsigned int) ; 
 unsigned int pc87413_get_swc_base () ; 
 int /*<<< orphan*/  pc87413_programm_wdto (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc87413_select_wdt_out () ; 
 int /*<<< orphan*/  pc87413_swc_bank3 (unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static void pc87413_enable(void)
{
	unsigned int swc_base_addr;

	spin_lock(&io_lock);

	pc87413_select_wdt_out();
	pc87413_enable_swc();
	swc_base_addr = pc87413_get_swc_base();
	pc87413_swc_bank3(swc_base_addr);
	pc87413_programm_wdto(swc_base_addr, timeout);
	pc87413_enable_wden(swc_base_addr);
	pc87413_enable_sw_wd_tren(swc_base_addr);
	pc87413_enable_sw_wd_trg(swc_base_addr);

	spin_unlock(&io_lock);
}