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
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int hb_add_json (int /*<<< orphan*/ *,char*) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 

int
ghb_add_job(hb_handle_t *h, GhbValue *job_dict)
{
    char     * json_job;
    int        sequence_id;

    json_job = hb_value_get_json(job_dict);
    sequence_id = hb_add_json(h, json_job);
    free(json_job);

    return sequence_id;
}