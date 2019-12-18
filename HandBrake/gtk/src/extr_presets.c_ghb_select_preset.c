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
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_preset_search_index (char const*,int,int) ; 
 int /*<<< orphan*/  select_preset2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
ghb_select_preset(signal_user_data_t *ud, const char *name, int type)
{
    hb_preset_index_t *path;

    path = hb_preset_search_index(name, 1, type);
    if (path != NULL)
    {
        select_preset2(ud, path);
        free(path);
    }
}