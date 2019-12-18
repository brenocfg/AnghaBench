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
 char* fix_name_collisions (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 char* hb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_dict_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 char* hb_strdup_printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_array_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_incref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void import_folder_hierarchy_29_0_0(const char * name,
                                    hb_value_t * new_list, hb_value_t * folder)
{
    hb_value_t * list = hb_dict_get(folder, "ChildrenArray");
    int          ii, count;

    count = hb_value_array_len(list);
    for (ii = 0; ii < count;)
    {
        hb_value_t * item = hb_value_array_get(list, ii);

        if (hb_dict_get_bool(item, "Folder"))
        {
            const char * folder_name;
            char       * new_name;
            int          pos = hb_value_array_len(new_list);

            folder_name = hb_dict_get_string(item, "PresetName");
            new_name = hb_strdup_printf("%s - %s", name, folder_name);
            import_folder_hierarchy_29_0_0(new_name, new_list, item);

            hb_value_t * children = hb_dict_get(item, "ChildrenArray");
            if (hb_value_array_len(children) > 0)
            {
                // If the folder has any children, move it to the
                // top level folder list.
                char * unique_name = fix_name_collisions(new_list, new_name);
                hb_dict_set_string(item, "PresetName", unique_name);
                hb_value_incref(item);
                hb_value_array_remove(list, ii);
                hb_value_array_insert(new_list, pos, item);
                free(unique_name);
            }
            else
            {
                hb_value_array_remove(list, ii);
            }
            free(new_name);
        }
        else
        {
            ii++;
        }
    }
}