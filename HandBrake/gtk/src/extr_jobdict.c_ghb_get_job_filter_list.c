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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_dict_new () ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_filter_settings (int /*<<< orphan*/ *) ; 

GhbValue* ghb_get_job_filter_list(GhbValue *settings)
{
    GhbValue *filter = ghb_get_job_filter_settings(settings);
    GhbValue *list   = ghb_dict_get(filter, "FilterList");
    if (list == NULL)
    {
        list = ghb_dict_new();
        ghb_dict_set(filter, "FilterList", list);
    }
    return list;
}