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
typedef  int /*<<< orphan*/  GhbSurface ;
typedef  int /*<<< orphan*/  GdkMonitor ;
typedef  int /*<<< orphan*/  GdkDisplay ;

/* Variables and functions */
 int /*<<< orphan*/ * gdk_display_get_monitor_at_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline GdkMonitor *
ghb_display_get_monitor_at_surface(GdkDisplay * display, GhbSurface * surface)
{
    return gdk_display_get_monitor_at_window(display, surface);
}