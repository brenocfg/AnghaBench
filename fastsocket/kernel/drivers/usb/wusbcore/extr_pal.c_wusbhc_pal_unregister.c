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
struct wusbhc {int /*<<< orphan*/  pal; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_pal_unregister (int /*<<< orphan*/ *) ; 

void wusbhc_pal_unregister(struct wusbhc *wusbhc)
{
	uwb_pal_unregister(&wusbhc->pal);
}