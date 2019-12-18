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
struct omapfb_update_window {int dummy; } ;
struct fb_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ update_mode; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ OMAPFB_UPDATE_DISABLED ; 
 TYPE_1__ dispc ; 

__attribute__((used)) static int omap_dispc_update_window(struct fb_info *fbi,
				 struct omapfb_update_window *win,
				 void (*complete_callback)(void *arg),
				 void *complete_callback_data)
{
	return dispc.update_mode == OMAPFB_UPDATE_DISABLED ? -ENODEV : 0;
}