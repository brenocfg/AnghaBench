#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int depth; } ;
struct TYPE_5__ {TYPE_1__ path; } ;
typedef  TYPE_2__ preset_do_context_t ;
typedef  int /*<<< orphan*/  hb_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_PRESET_JSON_FILE ; 
 int /*<<< orphan*/  HB_PRESET_PLIST_FILE ; 
 int /*<<< orphan*/  do_delete_builtin ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/  hb_get_user_config_filename (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_plist_parse_file (char*) ; 
 int hb_presets_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_read_json (char*) ; 
 int /*<<< orphan*/  presets_do (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

int hb_presets_gui_init(void)
{
    char path[1024];
    hb_value_t * dict = NULL;

#if defined(HB_PRESET_JSON_FILE)
    hb_get_user_config_filename(path, "%s", HB_PRESET_JSON_FILE);
    dict = hb_value_read_json(path);
#endif
#if defined(HB_PRESET_PLIST_FILE)
    if (dict == NULL)
    {
        hb_get_user_config_filename(path, "%s", HB_PRESET_PLIST_FILE);
        dict = hb_plist_parse_file(path);
    }
#endif
    if (dict == NULL)
    {
        hb_error("Failed to load GUI presets file");
#if defined(HB_PRESET_JSON_FILE)
        hb_error("Attempted: %s", HB_PRESET_JSON_FILE);
#endif
#if defined(HB_PRESET_PLIST_FILE)
        hb_error("Attempted: %s", HB_PRESET_PLIST_FILE);
#endif
        return -1;
    }
    else
    {
        preset_do_context_t ctx;
        ctx.path.depth = 1;
        presets_do(do_delete_builtin, dict, &ctx);
        int result = hb_presets_add(dict);
        hb_value_free(&dict);
        return result;
    }
    return -1;
}