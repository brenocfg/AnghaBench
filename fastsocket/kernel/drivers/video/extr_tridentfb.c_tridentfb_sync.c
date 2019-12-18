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
struct tridentfb_par {int /*<<< orphan*/  (* wait_engine ) (struct tridentfb_par*) ;} ;
struct fb_info {int flags; struct tridentfb_par* par; } ;

/* Variables and functions */
 int FBINFO_HWACCEL_DISABLED ; 
 int /*<<< orphan*/  stub1 (struct tridentfb_par*) ; 

__attribute__((used)) static int tridentfb_sync(struct fb_info *info)
{
	struct tridentfb_par *par = info->par;

	if (!(info->flags & FBINFO_HWACCEL_DISABLED))
		par->wait_engine(par);
	return 0;
}