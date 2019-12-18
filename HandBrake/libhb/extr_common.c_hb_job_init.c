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
typedef  int /*<<< orphan*/  hb_title_t ;
typedef  int /*<<< orphan*/  hb_job_t ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  job_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

hb_job_t * hb_job_init( hb_title_t * title )
{
    hb_job_t * job;

    if ( title == NULL )
        return NULL;

    job = calloc( sizeof( hb_job_t ), 1 );
    job_setup(job, title);

    return job;
}