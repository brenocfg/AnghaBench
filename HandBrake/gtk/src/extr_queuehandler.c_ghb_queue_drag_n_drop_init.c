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
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_ACTION_MOVE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int GTK_DEST_DEFAULT_DROP ; 
 int GTK_DEST_DEFAULT_MOTION ; 
 int /*<<< orphan*/  gtk_drag_dest_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_drag_entries ; 

void
ghb_queue_drag_n_drop_init(signal_user_data_t * ud)
{
    GtkWidget * widget;

    widget = GHB_WIDGET(ud->builder, "queue_list");
    gtk_drag_dest_set(widget, GTK_DEST_DEFAULT_MOTION|GTK_DEST_DEFAULT_DROP,
                      queue_drag_entries, 1, GDK_ACTION_MOVE);
}