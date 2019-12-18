#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  settings_array; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ ) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_queue_selection_init (TYPE_1__*) ; 
 int /*<<< orphan*/  queue_add (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_multiple_titles(signal_user_data_t *ud)
{
    gint count, ii;

    count = ghb_array_len(ud->settings_array);
    for (ii = 0; ii < count; ii++)
    {
        GhbValue *settings;

        settings = ghb_array_get(ud->settings_array, ii);
        if (ghb_dict_get_bool(settings, "title_selected"))
        {
            queue_add(ud, settings, 1);
        }
    }
    ghb_queue_selection_init(ud);
}