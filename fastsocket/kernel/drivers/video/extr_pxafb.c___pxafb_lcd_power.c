#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  var; } ;
struct pxafb_info {TYPE_1__ fb; int /*<<< orphan*/  (* lcd_power ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __pxafb_lcd_power(struct pxafb_info *fbi, int on)
{
	pr_debug("pxafb: LCD power o%s\n", on ? "n" : "ff");

	if (fbi->lcd_power)
		fbi->lcd_power(on, &fbi->fb.var);
}