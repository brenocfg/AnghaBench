#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int count; TYPE_1__* ud; } ;
typedef  TYPE_2__ button_click_t ;
struct TYPE_4__ {int /*<<< orphan*/  builder; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
easter_egg_timeout_cb(button_click_t *bc)
{
    if (bc->count == 1)
    {
        GtkWidget *widget;
        widget = GHB_WIDGET(bc->ud->builder, "allow_tweaks");
        gtk_widget_hide(widget);
        widget = GHB_WIDGET(bc->ud->builder, "hbfd_feature");
        gtk_widget_hide(widget);
    }
    bc->count = 0;

    return FALSE;
}