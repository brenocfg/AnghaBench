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
struct TYPE_3__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_LABEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_break_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_lookup_title (int,int*) ; 
 int /*<<< orphan*/  ghb_title_range_get_duration (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gtk_label_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
update_title_duration(signal_user_data_t *ud)
{
    gint hh, mm, ss;
    gint64 duration;
    gchar *text;
    GtkWidget *widget;
    int title_id, titleindex;
    const hb_title_t *title;

    title_id = ghb_dict_get_int(ud->settings, "title");
    title = ghb_lookup_title(title_id, &titleindex);
    widget = GHB_WIDGET (ud->builder, "title_duration");

    duration = ghb_title_range_get_duration(ud->settings, title);
    ghb_break_duration(duration, &hh, &mm, &ss);

    text = g_strdup_printf("%02d:%02d:%02d", hh, mm, ss);
    gtk_label_set_text(GTK_LABEL(widget), text);
    g_free(text);
}