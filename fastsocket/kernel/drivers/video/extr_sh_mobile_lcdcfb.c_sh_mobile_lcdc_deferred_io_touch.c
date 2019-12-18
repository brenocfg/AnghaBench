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
struct fb_info {int /*<<< orphan*/  deferred_work; struct fb_deferred_io* fbdefio; } ;
struct fb_deferred_io {int /*<<< orphan*/  delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mobile_lcdc_deferred_io_touch(struct fb_info *info)
{
	struct fb_deferred_io *fbdefio = info->fbdefio;

	if (fbdefio)
		schedule_delayed_work(&info->deferred_work, fbdefio->delay);
}