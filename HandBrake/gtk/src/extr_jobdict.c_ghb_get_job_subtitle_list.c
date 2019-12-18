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
 int /*<<< orphan*/ * ghb_array_new () ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_settings (int /*<<< orphan*/ *) ; 

GhbValue *ghb_get_job_subtitle_list(GhbValue *settings)
{
    GhbValue *sub_dict = ghb_get_job_subtitle_settings(settings);
    GhbValue *sub_list = ghb_dict_get(sub_dict, "SubtitleList");
    if (sub_list == NULL)
    {
        sub_list = ghb_array_new();
        ghb_dict_set(sub_dict, "SubtitleList", sub_list);
    }
    return sub_list;
}