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
 int hb_presets_import (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_json (char const*) ; 

int hb_presets_import_json(const char *in, char **out)
{
    int result;

    if (out != NULL)
    {
        *out = NULL;
    }
    hb_value_t * dict = hb_value_json(in);
    if (dict == NULL)
        return 0;

    hb_value_t * imported;
    result = hb_presets_import(dict, &imported);
    if (out != NULL)
    {
        *out = hb_value_get_json(imported);
    }
    hb_value_free(&dict);
    hb_value_free(&imported);
    return result;
}