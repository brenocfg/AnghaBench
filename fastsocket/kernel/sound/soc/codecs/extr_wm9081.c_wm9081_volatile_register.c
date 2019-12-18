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
#define  WM9081_SOFTWARE_RESET 128 

__attribute__((used)) static int wm9081_volatile_register(unsigned int reg)
{
	switch (reg) {
	case WM9081_SOFTWARE_RESET:
		return 1;
	default:
		return 0;
	}
}