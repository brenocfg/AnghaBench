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
struct nvidia_par {int lockup; } ;
struct TYPE_2__ {int scan_align; } ;
struct fb_info {TYPE_1__ pixmap; struct nvidia_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  touch_softlockup_watchdog () ; 

__attribute__((used)) static inline void nvidiafb_safe_mode(struct fb_info *info)
{
	struct nvidia_par *par = info->par;

	touch_softlockup_watchdog();
	info->pixmap.scan_align = 1;
	par->lockup = 1;
}