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
 unsigned long SWITCHER_ADDR ; 
 scalar_t__ start_switcher_text ; 

__attribute__((used)) static unsigned long switcher_offset(void)
{
	return SWITCHER_ADDR - (unsigned long)start_switcher_text;
}