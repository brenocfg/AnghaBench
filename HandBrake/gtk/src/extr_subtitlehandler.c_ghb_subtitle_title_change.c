#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_2__ hb_title_t ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* ghb_lookup_title (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_list_count (int /*<<< orphan*/ ) ; 

void
ghb_subtitle_title_change(signal_user_data_t *ud, gboolean show)
{
    GtkWidget *w = GHB_WIDGET(ud->builder, "subtitle_add");
    gtk_widget_set_sensitive(w, show);
    w = GHB_WIDGET(ud->builder, "subtitle_add_all");
    gtk_widget_set_sensitive(w, show);
    w = GHB_WIDGET(ud->builder, "subtitle_reset");
    gtk_widget_set_sensitive(w, show);

    int title_id;
    title_id = ghb_dict_get_int(ud->settings, "title");
    const hb_title_t *title = ghb_lookup_title(title_id, NULL);
    if (title != NULL)
    {
        w = GHB_WIDGET(ud->builder, "SubtitleImportDisable");
        gtk_widget_set_sensitive(w, !!hb_list_count(title->list_subtitle));
    }
}