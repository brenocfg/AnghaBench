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
 int /*<<< orphan*/ * hb_plist_parse_file (char const*) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_read_json (char const*) ; 

char * hb_presets_read_file_json(const char *filename)
{
    char *result;
    hb_value_t *preset = hb_value_read_json(filename);
    if (preset == NULL)
        preset = hb_plist_parse_file(filename);
    if (preset == NULL)
        return NULL;

    result = hb_value_get_json(preset);
    return result;
}