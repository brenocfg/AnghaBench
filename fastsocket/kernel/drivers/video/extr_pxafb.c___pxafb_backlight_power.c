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
struct pxafb_info {int /*<<< orphan*/  (* backlight_power ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static inline void __pxafb_backlight_power(struct pxafb_info *fbi, int on)
{
	pr_debug("pxafb: backlight o%s\n", on ? "n" : "ff");

	if (fbi->backlight_power)
		fbi->backlight_power(on);
}