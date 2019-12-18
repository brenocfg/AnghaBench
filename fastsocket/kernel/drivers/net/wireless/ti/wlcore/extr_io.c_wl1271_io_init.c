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
struct wl1271 {int /*<<< orphan*/  dev; TYPE_1__* if_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void wl1271_io_init(struct wl1271 *wl)
{
	if (wl->if_ops->init)
		wl->if_ops->init(wl->dev);
}