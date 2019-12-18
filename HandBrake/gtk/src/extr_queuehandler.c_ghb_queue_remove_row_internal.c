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
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int GHB_QUEUE_RUNNING ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,int) ; 
 int ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_array_remove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ghb_cancel_encode2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_remove_job (int) ; 
 int /*<<< orphan*/  gtk_container_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ghb_queue_remove_row_internal(signal_user_data_t *ud, int index)
{
    GtkListBox    * lb;
    GtkListBoxRow * row;
    GhbValue      * queueDict, * uiDict;

    if (index < 0 || index >= ghb_array_len(ud->queue))
    {
        return;
    }

    queueDict  = ghb_array_get(ud->queue, index);
    uiDict     = ghb_dict_get(queueDict, "uiSettings");
    int status = ghb_dict_get_int(uiDict, "job_status");
    if (status == GHB_QUEUE_RUNNING)
    {
        // Ask if wants to stop encode.
        if (!ghb_cancel_encode2(ud, NULL))
        {
            return;
        }
        int unique_id = ghb_dict_get_int(uiDict, "job_unique_id");
        ghb_remove_job(unique_id);
    }
    ghb_array_remove(ud->queue, index);

    // Update UI
    lb  = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "queue_list"));
    row = gtk_list_box_get_row_at_index(lb, index);
    gtk_container_remove(GTK_CONTAINER(lb), GTK_WIDGET(row));
}