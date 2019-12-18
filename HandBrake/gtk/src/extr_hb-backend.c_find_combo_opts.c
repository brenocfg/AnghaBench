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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  combo_opts_t ;
struct TYPE_3__ {int /*<<< orphan*/ * opts; } ;
typedef  TYPE_1__ combo_name_map_t ;

/* Variables and functions */
 TYPE_1__* find_combo_map (int /*<<< orphan*/  const*) ; 

combo_opts_t*
find_combo_opts(const gchar *name)
{
    combo_name_map_t *entry = find_combo_map(name);
    if (entry != NULL)
    {
        return entry->opts;
    }
    return NULL;
}