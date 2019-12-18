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
 int /*<<< orphan*/  HB_PRESET_TYPE_CUSTOM ; 
 scalar_t__ HB_PRESET_TYPE_OFFICIAL ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 char* fix_name_collisions (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hb_dict_get_int (int /*<<< orphan*/ *,char*) ; 
 char* hb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_dict_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hb_dict_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_dict_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 
 int /*<<< orphan*/  hb_value_array_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * hb_value_dup (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_folder_hierarchy_29_0_0 (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static hb_value_t * import_hierarchy_29_0_0(hb_value_t *presets)
{
    hb_value_t * list = presets;
    hb_value_t * my_presets = NULL;
    hb_value_t * my_presets_list;
    hb_value_t * new_list;
    int          ii, count;

    if (hb_value_type(presets) == HB_VALUE_TYPE_DICT &&
        hb_dict_get(presets, "VersionMajor") != NULL)
    {
        // A packaged preset list
        list = hb_dict_get(presets, "PresetList");
    }

    // Copy official presets to new list
    new_list = hb_value_array_init();
    count = hb_value_array_len(list);
    for (ii = 0; ii < count; ii++)
    {
        hb_value_t * item = hb_value_array_get(list, ii);
        if (hb_dict_get_int(item, "Type") != HB_PRESET_TYPE_OFFICIAL)
        {
            continue;
        }
        hb_value_array_append(new_list, hb_value_dup(item));
    }

    // First process any custom folder named "My Presets".
    // Any existing "My Presets" folder is sanitized for subfolders.
    // If "My Presets" doesn't exist, one is created.
    count = hb_value_array_len(list);
    for (ii = 0; ii < count; ii++)
    {
        hb_value_t * item = hb_value_array_get(list, ii);

        if (hb_dict_get_int(item, "Type") == HB_PRESET_TYPE_OFFICIAL)
        {
            // Skip official presets.  The don't need to be restructured.
            continue;
        }
        if (hb_dict_get_bool(item, "Folder"))
        {
            int          pos = hb_value_array_len(new_list);
            const char * name = hb_dict_get_string(item, "PresetName");
            if (strcmp(name, "My Presets"))
            {
                continue;
            }
            import_folder_hierarchy_29_0_0(name, new_list, item);

            my_presets = hb_value_dup(item);
            hb_value_array_insert(new_list, pos, my_presets);
            hb_value_array_remove(list, ii);
            break;
        }
    }
    if (my_presets == NULL)
    {
        my_presets = hb_dict_init();
        hb_dict_set_string(my_presets, "PresetName", "My Presets");
        hb_dict_set(my_presets, "ChildrenArray", hb_value_array_init());
        hb_dict_set_int(my_presets, "Type", HB_PRESET_TYPE_CUSTOM);
        hb_dict_set_bool(my_presets, "Folder", 1);
        hb_value_array_append(new_list, my_presets);
    }
    my_presets_list = hb_dict_get(my_presets, "ChildrenArray");

    // Sanitize all other custom folders
    count = hb_value_array_len(list);
    for (ii = 0; ii < count; ii++)
    {
        hb_value_t * item = hb_value_array_get(list, ii);

        if (hb_dict_get_int(item, "Type") == HB_PRESET_TYPE_OFFICIAL)
        {
            // Skip official presets.  The don't need to be restructured.
            continue;
        }
        if (hb_dict_get_bool(item, "Folder"))
        {
            int          pos  = hb_value_array_len(new_list);
            const char * name = hb_dict_get_string(item, "PresetName");
            import_folder_hierarchy_29_0_0(name, new_list, item);

            hb_value_t * children = hb_dict_get(item, "ChildrenArray");
            if (hb_value_array_len(children) > 0)
            {
                // If the folder has any children, move it to the
                // top level folder list.
                char * unique_name = fix_name_collisions(new_list, name);
                hb_dict_set_string(item, "PresetName", unique_name);
                hb_value_array_insert(new_list, pos, hb_value_dup(item));
                free(unique_name);
            }
        }
        else
        {
            hb_value_array_append(my_presets_list, hb_value_dup(item));
        }
    }

    if (hb_value_type(presets) == HB_VALUE_TYPE_DICT &&
        hb_dict_get(presets, "VersionMajor") != NULL)
    {
        // A packaged preset list
        hb_dict_set(presets, "PresetList", new_list);
    }
    else
    {
        presets = new_list;
    }
    return hb_value_dup(presets);
}