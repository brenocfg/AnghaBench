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
 int /*<<< orphan*/ * hb_generate_filter_settings (int,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 

char *
hb_generate_filter_settings_json(int filter_id, const char *preset,
                                 const char *tune, const char *custom)
{
    hb_value_t * settings;

    settings = hb_generate_filter_settings(filter_id, preset, tune, custom);
    if (settings == NULL)
    {
        return NULL;
    }

    char * result = hb_value_get_json(settings);
    hb_value_free(&settings);
    return result;
}