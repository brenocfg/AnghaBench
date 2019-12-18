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
typedef  int /*<<< orphan*/  hb_job_t ;
typedef  int /*<<< orphan*/  hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_add_filter_dict (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/ * hb_parse_filter_settings (char const*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 

void hb_add_filter( hb_job_t * job, hb_filter_object_t * filter,
                    const char * settings_in )
{
    hb_dict_t * settings = hb_parse_filter_settings(settings_in);
    if (settings_in != NULL && settings == NULL)
    {
        hb_log("hb_add_filter: failed to parse filter settings!");
        return;
    }
    hb_add_filter_dict(job, filter, settings);
    hb_value_free(&settings);
}