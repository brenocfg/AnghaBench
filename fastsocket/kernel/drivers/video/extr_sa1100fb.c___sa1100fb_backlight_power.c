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
struct sa1100fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,char*) ; 
 int /*<<< orphan*/  sa1100fb_backlight_power (int) ; 

__attribute__((used)) static inline void __sa1100fb_backlight_power(struct sa1100fb_info *fbi, int on)
{
	DPRINTK("backlight o%s\n", on ? "n" : "ff");

	if (sa1100fb_backlight_power)
		sa1100fb_backlight_power(on);
}