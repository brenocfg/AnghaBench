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
struct TYPE_4__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int int64_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkListBox ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_LIST_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * create_chapter_row (scalar_t__,int,int,char const*,TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_get_job_chapter_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_box_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
chapter_refresh_list_ui(signal_user_data_t *ud)
{
    GhbValue   * chapter_list;
    GtkListBox * lb;
    GtkWidget  * row;
    gint         ii, count;

    lb = GTK_LIST_BOX(GHB_WIDGET(ud->builder, "chapters_list"));

    chapter_list = ghb_get_job_chapter_list(ud->settings);
    count = ghb_array_len(chapter_list);
    for (ii = 0; ii < count; ii++)
    {
        GhbValue   * chapter_dict;
        GhbValue   * duration_dict;
        const char * name;
        int64_t start = 0, duration;

        chapter_dict  = ghb_array_get(chapter_list, ii);
        name          = ghb_dict_get_string(chapter_dict, "Name");
        duration_dict = ghb_dict_get(chapter_dict, "Duration");
        duration      = ghb_dict_get_int(duration_dict, "Ticks") / 90000;
        row           = create_chapter_row(ii + 1, start, duration, name, ud);
        start        += duration;

        gtk_list_box_insert(lb, row, -1);
    }
}