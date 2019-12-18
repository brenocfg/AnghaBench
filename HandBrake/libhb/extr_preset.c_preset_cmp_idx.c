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
 int HB_PRESET_TYPE_ALL ; 
 int PRESET_DO_NEXT ; 
 int PRESET_DO_PARTIAL ; 
 int PRESET_DO_SKIP ; 
 int PRESET_DO_SUCCESS ; 
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int hb_value_get_int (int /*<<< orphan*/ ) ; 
 char* hb_value_get_string (int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int preset_cmp_idx(hb_value_t *preset, int idx,
                          const char *name, int type)
{
    const char *next, *preset_name;
    int  ii, len;

    if (type != HB_PRESET_TYPE_ALL &&
        type != hb_value_get_int(hb_dict_get(preset, "Type")))
    {
        return PRESET_DO_NEXT;
    }

    // Strip leading '/'
    if (name[0] == '/')
        name++;

    // Find the part of the "name" path we want to match.
    for (ii = 0; ii < idx; ii++)
    {
        next = strchr(name, '/');
        if (next == NULL)
            return PRESET_DO_SKIP;
        next++;
        name = next;
    }

    // Find the end of the part we want to match
    next = strchr(name, '/');
    if (next != NULL)
        len = next - name;
    else
        len = strlen(name);
    if (len <= 0)
        return PRESET_DO_SKIP;

    preset_name = hb_value_get_string(hb_dict_get(preset, "PresetName"));
    if (strlen(preset_name) > len)
        len = strlen(preset_name);

    // If match found and it's the last component of the "name", success!
    if (!strncmp(name, preset_name, len))
    {
        if (name[len] == 0)
            return PRESET_DO_SUCCESS;
        else
            return PRESET_DO_PARTIAL;
    }
    return PRESET_DO_NEXT;
}