#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_3__ {int /*<<< orphan*/ * name; int /*<<< orphan*/ * short_name; } ;
typedef  TYPE_1__ hb_filter_param_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 TYPE_1__* filter_param_get_presets_internal (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_string (int /*<<< orphan*/ *) ; 

char * hb_filter_get_presets_json(int filter_id)
{
    hb_value_array_t  * array = hb_value_array_init();
    int                 ii, count = 0;
    hb_filter_param_t * table;

    table = filter_param_get_presets_internal(filter_id, NULL);

    for (count = 0; table[count].name != NULL; count++);
    for (ii = 0; ii < count; ii++)
    {
        hb_dict_t * dict = hb_dict_init();
        hb_dict_set(dict, "short_name", hb_value_string(table[ii].short_name));
        hb_dict_set(dict, "name", hb_value_string(table[ii].name));
        hb_value_array_append(array, dict);
    }

    char * result = hb_value_get_json(array);
    hb_value_free(&array);
    return result;
}