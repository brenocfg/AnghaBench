#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_interjob_t ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {void* list_title; } ;
struct TYPE_9__ {int pause_date; int /*<<< orphan*/  main_thread; scalar_t__ die; void* interjob; void* pause_lock; TYPE_2__ state; void* state_lock; void* jobs; TYPE_1__ title_set; int /*<<< orphan*/  system_sleep_opaque; scalar_t__ id; } ;
typedef  TYPE_3__ hb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_NORMAL_PRIORITY ; 
 int /*<<< orphan*/  HB_STATE_IDLE ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  hb_instance_counter ; 
 void* hb_list_init () ; 
 void* hb_lock_init () ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  hb_log_level_set (TYPE_3__*,int) ; 
 int /*<<< orphan*/  hb_system_sleep_opaque_init () ; 
 int /*<<< orphan*/  hb_thread_init (char*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_func ; 

hb_handle_t * hb_init( int verbose )
{
    hb_handle_t * h = calloc( sizeof( hb_handle_t ), 1 );

    /* See hb_deep_log() and hb_log() in common.c */
    hb_log_level_set(h, verbose);

    h->id = hb_instance_counter++;

    /* Initialize opaque for PowerManagement purposes */
    h->system_sleep_opaque = hb_system_sleep_opaque_init();

	h->title_set.list_title = hb_list_init();
    h->jobs       = hb_list_init();

    h->state_lock  = hb_lock_init();
    h->state.state = HB_STATE_IDLE;

    h->pause_lock = hb_lock_init();
    h->pause_date = -1;

    h->interjob = calloc( sizeof( hb_interjob_t ), 1 );

    /* Start library thread */
    hb_log( "hb_init: starting libhb thread" );
    h->die         = 0;
    h->main_thread = hb_thread_init( "libhb", thread_func, h,
                                     HB_NORMAL_PRIORITY );

    return h;
}