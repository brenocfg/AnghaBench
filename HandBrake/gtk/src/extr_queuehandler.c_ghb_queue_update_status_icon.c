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
struct TYPE_3__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GtkImage ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_ICON_SIZE_BUTTON ; 
#define  GHB_QUEUE_CANCELED 132 
#define  GHB_QUEUE_DONE 131 
#define  GHB_QUEUE_FAIL 130 
#define  GHB_QUEUE_PENDING 129 
#define  GHB_QUEUE_RUNNING 128 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_IMAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_widget (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,int) ; 
 int ghb_array_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_image_set_from_icon_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_list_box_get_row_at_index (int /*<<< orphan*/ *,int) ; 

void
ghb_queue_update_status_icon(signal_user_data_t *ud, int index)
{
    int count = ghb_array_len(ud->queue);
    if (index < 0 || index >= count)
    {
        // invalid index
        return;
    }

    GhbValue * queueDict, * uiDict;
    queueDict = ghb_array_get(ud->queue, index);
    if (queueDict == NULL) // should never happen
    {
        return;
    }
    uiDict    = ghb_dict_get(queueDict, "uiSettings");
    if (uiDict == NULL) // should never happen
    {
        return;
    }

    int status = ghb_dict_get_int(uiDict, "job_status");

    // Now update the UI
    const char * icon_name;
    switch (status)
    {
        case GHB_QUEUE_RUNNING:
             icon_name = "hb-start";
            break;
        case GHB_QUEUE_PENDING:
             icon_name = "hb-source";
            break;
        case GHB_QUEUE_FAIL:
        case GHB_QUEUE_CANCELED:
             icon_name = "hb-stop";
            break;
        case GHB_QUEUE_DONE:
             icon_name = "hb-complete";
            break;
        default:
             icon_name = "hb-source";
            break;
    }
    GtkListBox    * lb;
    GtkListBoxRow * row;
    GtkImage      * status_icon;

    lb = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "queue_list"));
    row = gtk_list_box_get_row_at_index(lb, index);
    if (row == NULL) // should never happen
    {
        return;
    }
    status_icon = GTK_IMAGE(find_widget(GTK_WIDGET(row), "queue_item_status"));
    if (status_icon == NULL) // should never happen
    {
        return;
    }
    ghb_image_set_from_icon_name(status_icon, icon_name,
                                 GHB_ICON_SIZE_BUTTON);
}