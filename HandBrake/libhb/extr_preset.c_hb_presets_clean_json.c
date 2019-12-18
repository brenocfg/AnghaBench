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
 int /*<<< orphan*/  hb_preset_template ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_json (char const*) ; 
 int /*<<< orphan*/  presets_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char * hb_presets_clean_json(const char *json)
{
    hb_value_t * dict = hb_value_json(json);
    if (dict == NULL)
        return NULL;

    presets_clean(dict, hb_preset_template);
    char * result = hb_value_get_json(dict);
    hb_value_free(&dict);
    return result;
}