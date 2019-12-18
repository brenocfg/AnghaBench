#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  add_to_subtitle_list_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_live_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_subtitle_to_ui(signal_user_data_t *ud, GhbValue *subsettings)
{
    if (subsettings == NULL)
        return;

    // Add the current subtitle settings to the list.
    add_to_subtitle_list_ui(ud, subsettings);
    ghb_live_reset(ud);
}