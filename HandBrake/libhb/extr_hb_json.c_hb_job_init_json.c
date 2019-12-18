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
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_job_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_job_init_by_index (int /*<<< orphan*/ *,int) ; 
 char* hb_job_to_json (int /*<<< orphan*/ *) ; 

char* hb_job_init_json(hb_handle_t *h, int title_index)
{
    hb_job_t *job = hb_job_init_by_index(h, title_index);
    char *json_job = hb_job_to_json(job);
    hb_job_close(&job);
    return json_job;
}