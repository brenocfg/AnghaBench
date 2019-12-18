#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GdkWindow ;
typedef  int /*<<< orphan*/  GVolumeMonitor ;
typedef  int /*<<< orphan*/  GCallback ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ drive_changed_cb ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * g_volume_monitor_get () ; 
 int /*<<< orphan*/  gdk_window_add_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * gtk_widget_get_parent_window (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_message_cb ; 

void
watch_volumes(signal_user_data_t *ud)
{
#if !defined(_WIN32)
    GVolumeMonitor *gvm;
    gvm = g_volume_monitor_get();

    g_signal_connect(gvm, "drive-changed", (GCallback)drive_changed_cb, ud);
#else
    GdkWindow *window;
    GtkWidget *widget;

    widget = GHB_WIDGET(ud->builder, "hb_window");
    window = gtk_widget_get_parent_window(widget);
    gdk_window_add_filter(window, win_message_cb, ud);
#endif
}