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
 int /*<<< orphan*/  w83697hf_set_reg (int,int) ; 
 int /*<<< orphan*/  w83697hf_unlock () ; 

__attribute__((used)) static void w83697hf_select_wdt(void)
{
	w83697hf_unlock();
	w83697hf_set_reg(0x07, 0x08);	/* Switch to logic device 8 (GPIO2) */
}