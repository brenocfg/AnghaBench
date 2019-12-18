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
struct TYPE_3__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  GtkListBoxRow ;
typedef  int /*<<< orphan*/  GtkEditable ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ *,char*,char const*) ; 
 char* ghb_editable_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_chapter_list (int /*<<< orphan*/ ) ; 
 int gtk_list_box_row_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_box_get_row (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
chapter_changed_cb(
    GtkEditable * edit,
    signal_user_data_t *ud)
{
    GtkListBoxRow * row;
    const char    * text;
    int             index;

    row = list_box_get_row(GTK_WIDGET(edit));
    if (row == NULL)
    {
        return;
    }
    index = gtk_list_box_row_get_index(row);
    text  = ghb_editable_get_text(edit);
    if (text == NULL)
    {
        return;
    }

    const GhbValue * chapter_list;
    GhbValue       * chapter_dict;

    chapter_list = ghb_get_job_chapter_list(ud->settings);
    chapter_dict = ghb_array_get(chapter_list, index);
    if (chapter_dict == NULL)
    {
        return;
    }
    ghb_dict_set_string(chapter_dict, "Name", text);
}