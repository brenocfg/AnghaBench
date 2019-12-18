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
struct TYPE_5__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ghb_dict_get_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_ui_update (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_destination_settings (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_destination(signal_user_data_t *ud)
{
    set_destination_settings(ud, ud->settings);
    ghb_ui_update(ud, "dest_file",
        ghb_dict_get_value(ud->settings, "dest_file"));
}