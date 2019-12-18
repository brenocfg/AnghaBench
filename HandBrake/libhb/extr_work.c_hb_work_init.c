#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int volatile* die; int /*<<< orphan*/ * error; int /*<<< orphan*/ ** current_job; int /*<<< orphan*/ * jobs; } ;
typedef  TYPE_1__ hb_work_t ;
typedef  int /*<<< orphan*/  hb_thread_t ;
typedef  int /*<<< orphan*/  hb_list_t ;
typedef  int /*<<< orphan*/  hb_job_t ;
typedef  int /*<<< orphan*/  hb_error_code ;

/* Variables and functions */
 int /*<<< orphan*/  HB_LOW_PRIORITY ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/ * hb_thread_init (char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_func ; 

hb_thread_t * hb_work_init( hb_list_t * jobs, volatile int * die, hb_error_code * error, hb_job_t ** job )
{
    hb_work_t * work = calloc( sizeof( hb_work_t ), 1 );

    work->jobs      = jobs;
    work->current_job = job;
    work->die       = die;
    work->error     = error;

    return hb_thread_init( "work", work_func, work, HB_LOW_PRIORITY );
}