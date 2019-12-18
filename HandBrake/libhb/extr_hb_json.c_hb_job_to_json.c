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
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_job_to_dict (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 char* hb_value_get_json (int /*<<< orphan*/ *) ; 

char* hb_job_to_json( const hb_job_t * job )
{
    hb_dict_t *dict = hb_job_to_dict(job);

    if (dict == NULL)
        return NULL;

    char *json_job = hb_value_get_json(dict);
    hb_value_free(&dict);

    return json_job;
}