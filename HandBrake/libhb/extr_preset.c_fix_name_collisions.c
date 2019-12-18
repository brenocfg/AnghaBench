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
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* hb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 char* hb_strdup_printf (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char * fix_name_collisions(hb_value_t * list, const char * name)
{
    char * new_name = strdup(name);
    int    ii, jj, count;

    count = hb_value_array_len(list);
    for (ii = 0, jj = 0; ii < count; ii++)
    {
        hb_value_t * item = hb_value_array_get(list, ii);
        const char * preset_name;

        preset_name = hb_dict_get_string(item, "PresetName");
        if (!strcmp(new_name, preset_name))
        {
            // Collision, add a number and try again
            free(new_name);
            new_name = hb_strdup_printf("%s - %d", name, jj++);
            ii = -1;
        }
    }
    return new_name;
}