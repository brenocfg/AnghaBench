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
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
subtitle_exclusive_default_settings(GhbValue *settings, gint index)
{
    GhbValue *subtitle_list;
    GhbValue *subtitle;
    gint ii, count;

    subtitle_list = ghb_get_job_subtitle_list(settings);
    count = ghb_array_len(subtitle_list);
    for (ii = 0; ii < count; ii++)
    {
        if (ii != index)
        {
            subtitle = ghb_array_get(subtitle_list, ii);
            ghb_dict_set_bool(subtitle, "Default", FALSE);
        }
    }
}