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
struct fb_var_screeninfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  var; } ;
struct cfb_info {TYPE_1__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct fb_var_screeninfo*,int /*<<< orphan*/ *,int) ; 

void cyber2000fb_get_fb_var(struct cfb_info *cfb, struct fb_var_screeninfo *var)
{
	memcpy(var, &cfb->fb.var, sizeof(struct fb_var_screeninfo));
}