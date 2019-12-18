#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 
 scalar_t__ hud_timeout_id ; 

__attribute__((used)) static gboolean
hud_timeout(signal_user_data_t *ud)
{
    GtkWidget *widget;

    g_debug("hud_timeout()");
    widget = GHB_WIDGET(ud->builder, "preview_hud");
    gtk_widget_hide(widget);
    hud_timeout_id = 0;
    return FALSE;
}