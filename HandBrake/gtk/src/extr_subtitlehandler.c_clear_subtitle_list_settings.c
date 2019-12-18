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
 int /*<<< orphan*/  ghb_array_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_search (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
clear_subtitle_list_settings(GhbValue *settings)
{
    GhbValue *subtitle_list, *subtitle_search;

    subtitle_list = ghb_get_job_subtitle_list(settings);
    subtitle_search = ghb_get_job_subtitle_search(settings);
    ghb_array_reset(subtitle_list);
    ghb_dict_set_bool(subtitle_search, "Enable", 0);
}