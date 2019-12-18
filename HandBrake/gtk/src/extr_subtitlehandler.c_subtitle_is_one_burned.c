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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,int) ; 
 int ghb_array_len (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_list (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean subtitle_is_one_burned(GhbValue *settings)
{
    GhbValue *subtitle_list, *subsettings;
    int count, ii;

    subtitle_list = ghb_get_job_subtitle_list(settings);
    if (subtitle_list == NULL)
        return FALSE;

    count = ghb_array_len(subtitle_list);
    for (ii = 0; ii < count; ii++)
    {
        subsettings = ghb_array_get(subtitle_list, ii);
        if (ghb_dict_get_bool(subsettings, "Burn"))
        {
            return TRUE;
        }
    }
    return FALSE;
}