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
struct TYPE_4__ {int /*<<< orphan*/ * job; int /*<<< orphan*/  end; int /*<<< orphan*/  mux; int /*<<< orphan*/  init; } ;
typedef  TYPE_1__ hb_mux_object_t ;
typedef  int /*<<< orphan*/  hb_job_t ;

/* Variables and functions */
 int /*<<< orphan*/  avformatEnd ; 
 int /*<<< orphan*/  avformatInit ; 
 int /*<<< orphan*/  avformatMux ; 
 TYPE_1__* calloc (int,int) ; 

hb_mux_object_t * hb_mux_avformat_init( hb_job_t * job )
{
    hb_mux_object_t * m = calloc( sizeof( hb_mux_object_t ), 1 );
    m->init      = avformatInit;
    m->mux       = avformatMux;
    m->end       = avformatEnd;
    m->job       = job;
    return m;
}