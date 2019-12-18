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
struct fb_info {int /*<<< orphan*/  deferred_work; TYPE_1__* fbops; struct fb_deferred_io* fbdefio; } ;
struct fb_deferred_io {scalar_t__ delay; int /*<<< orphan*/  pagelist; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb_mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_deferred_io_mmap ; 
 int /*<<< orphan*/  fb_deferred_io_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void fb_deferred_io_init(struct fb_info *info)
{
	struct fb_deferred_io *fbdefio = info->fbdefio;

	BUG_ON(!fbdefio);
	mutex_init(&fbdefio->lock);
	info->fbops->fb_mmap = fb_deferred_io_mmap;
	INIT_DELAYED_WORK(&info->deferred_work, fb_deferred_io_work);
	INIT_LIST_HEAD(&fbdefio->pagelist);
	if (fbdefio->delay == 0) /* set a default of 1 s */
		fbdefio->delay = HZ;
}