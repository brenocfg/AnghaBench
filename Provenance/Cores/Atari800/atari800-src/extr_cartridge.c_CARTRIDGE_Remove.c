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
 int /*<<< orphan*/  CARTRIDGE_Remove_Second () ; 
 int /*<<< orphan*/  CARTRIDGE_main ; 
 int /*<<< orphan*/  RemoveCart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * active_cart ; 

void CARTRIDGE_Remove(void)
{
	active_cart = &CARTRIDGE_main;
	CARTRIDGE_Remove_Second();
	RemoveCart(&CARTRIDGE_main);
}