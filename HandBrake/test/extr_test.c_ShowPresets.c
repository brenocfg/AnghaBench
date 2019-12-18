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
typedef  int /*<<< orphan*/  hb_value_array_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  Indent (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_presets_get () ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_get_bool (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char** str_width_split (char const*,int) ; 

__attribute__((used)) static void ShowPresets(hb_value_array_t *presets, int indent, int descriptions)
{
    if (presets == NULL)
        presets = hb_presets_get();

    int count = hb_value_array_len(presets);
    int ii;
    for (ii = 0; ii < count; ii++)
    {
        const char *name;
        hb_dict_t *preset_dict = hb_value_array_get(presets, ii);
        name = hb_value_get_string(hb_dict_get(preset_dict, "PresetName"));
        Indent(stderr, "    ", indent);
        if (hb_value_get_bool(hb_dict_get(preset_dict, "Folder")))
        {
            indent++;
            fprintf(stderr, "%s/\n", name);
            hb_value_array_t *children;
            children = hb_dict_get(preset_dict, "ChildrenArray");
            if (children == NULL)
                continue;
            ShowPresets(children, indent, descriptions);
            indent--;
        }
        else
        {
            fprintf(stderr, "%s\n", name);
            if (descriptions)
            {
                const char *desc;
                desc = hb_value_get_string(hb_dict_get(preset_dict,
                                                       "PresetDescription"));
                if (desc != NULL && desc[0] != 0)
                {
                    int ii;
                    char **split = str_width_split(desc, 60);
                    for (ii = 0; split[ii] != NULL; ii++)
                    {
                        Indent(stderr, "    ", indent+1);
                        fprintf(stderr, "%s\n", split[ii]);
                    }
                    hb_str_vfree(split);
                }
            }
        }
    }
}