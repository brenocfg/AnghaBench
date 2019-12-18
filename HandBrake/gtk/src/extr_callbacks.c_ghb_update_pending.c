#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkLabel ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_label_set_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int queue_pending_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_queue_labels (TYPE_1__*) ; 

void
ghb_update_pending(signal_user_data_t *ud)
{
    GtkLabel *label;
    gint pending;
    gchar *str;

    pending = queue_pending_count(ud->queue);
    if (pending == 1)
    {
        str = g_strdup_printf(_("%d encode pending"), pending);
    }
    else
    {
        str = g_strdup_printf(_("%d encodes pending"), pending);
    }
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "pending_status"));
    gtk_label_set_text(label, str);
    label = GTK_LABEL(GHB_WIDGET(ud->builder, "queue_status_label"));
    gtk_label_set_text(label, str);
    g_free(str);

    update_queue_labels(ud);
}