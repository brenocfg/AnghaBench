#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* json; } ;
typedef  TYPE_1__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;

/* Variables and functions */
 int hb_add (int /*<<< orphan*/ *,TYPE_1__*) ; 

int hb_add_json( hb_handle_t * h, const char * json_job )
{
    hb_job_t job;

    job.json = json_job;
    return hb_add(h, &job);
}