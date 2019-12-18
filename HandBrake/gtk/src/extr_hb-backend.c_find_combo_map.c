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
typedef  size_t gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ combo_name_map_t ;

/* Variables and functions */
 TYPE_1__* combo_name_map ; 
 scalar_t__ strcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

combo_name_map_t*
find_combo_map(const gchar *name)
{
    gint ii;

    for (ii = 0; combo_name_map[ii].name != NULL; ii++)
    {
        if (strcmp(name, combo_name_map[ii].name) == 0)
        {
            return &combo_name_map[ii];
        }
    }
    return NULL;
}