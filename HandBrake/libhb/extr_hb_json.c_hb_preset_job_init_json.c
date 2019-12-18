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
typedef  int /*<<< orphan*/  hb_handle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_preset_job_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_json (char const*) ; 

char* hb_preset_job_init_json(hb_handle_t *h, int title_index,
                              const char *json_preset)
{
    hb_dict_t * preset   = hb_value_json(json_preset);
    hb_dict_t * job      = hb_preset_job_init(h, title_index, preset);
    char      * json_job = hb_value_get_json(job);

    hb_value_free(&preset);
    hb_value_free(&job);

    return json_job;
}