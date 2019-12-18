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
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ghb_audio_title_change(signal_user_data_t *ud, gboolean title_valid)
{
    GtkWidget *w = GHB_WIDGET(ud->builder, "audio_add");
    gtk_widget_set_sensitive(w, title_valid);
    w = GHB_WIDGET(ud->builder, "audio_add_all");
    gtk_widget_set_sensitive(w, title_valid);
    w = GHB_WIDGET(ud->builder, "audio_reset");
    gtk_widget_set_sensitive(w, title_valid);
}