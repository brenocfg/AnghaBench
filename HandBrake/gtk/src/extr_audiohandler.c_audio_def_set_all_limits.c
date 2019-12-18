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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkListBox ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_def_set_all_limits_cb ; 
 int /*<<< orphan*/  gtk_container_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void audio_def_set_all_limits(signal_user_data_t *ud)
{
    GtkListBox *list_box;

    list_box = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "audio_list_default"));
    gtk_container_foreach(GTK_CONTAINER(list_box),
                          audio_def_set_all_limits_cb, (gpointer)ud);
}