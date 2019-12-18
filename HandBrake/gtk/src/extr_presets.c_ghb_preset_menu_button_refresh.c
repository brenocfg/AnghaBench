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
typedef  int /*<<< orphan*/  hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_preset_search_index (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_preset_menu_button_label (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ghb_preset_menu_button_refresh(signal_user_data_t *ud,
                               const char *fullname, int type)
{
    hb_preset_index_t * path;

    path = hb_preset_search_index(fullname, 0, type);
    set_preset_menu_button_label(ud, path);
}