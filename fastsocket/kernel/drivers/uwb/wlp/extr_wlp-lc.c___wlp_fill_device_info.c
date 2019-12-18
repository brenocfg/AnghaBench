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
struct wlp {int /*<<< orphan*/  dev_info; int /*<<< orphan*/  (* fill_device_info ) (struct wlp*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct wlp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void __wlp_fill_device_info(struct wlp *wlp)
{
	wlp->fill_device_info(wlp, wlp->dev_info);
}