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
struct TYPE_3__ {char* settings_template; } ;
typedef  TYPE_1__ hb_filter_object_t ;

/* Variables and functions */
 char** calloc (int,int) ; 
 TYPE_1__* hb_filter_get (int) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 char** hb_str_vsplit (char*,char) ; 
 char* strdup (char*) ; 

char ** hb_filter_get_keys(int filter_id)
{
    hb_filter_object_t * filter = hb_filter_get(filter_id);

    if (filter == NULL || filter->settings_template == NULL)
    {
        return NULL;
    }

    char ** tmpl = hb_str_vsplit(filter->settings_template, ':');
    int     ii, count = 0;

    for (ii = 0; tmpl[ii] != NULL; ii++)
    {
        count++;
    }
    char ** result = calloc(count + 1, sizeof(char*));
    for (ii = 0; tmpl[ii] != NULL; ii++)
    {
        char ** pair = hb_str_vsplit(tmpl[ii], '=');
        result[ii] = strdup(pair[0]);
        hb_str_vfree(pair);
    }
    result[ii] = NULL;
    hb_str_vfree(tmpl);

    return result;
}