#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int splice_list_size; struct TYPE_5__* splice_list; struct TYPE_5__* fifos; int /*<<< orphan*/  list; scalar_t__ stream; scalar_t__ dvd; scalar_t__ bd; } ;
typedef  TYPE_1__ hb_work_private_t ;
struct TYPE_6__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_work_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_bd_close (scalar_t__*) ; 
 int /*<<< orphan*/  hb_bd_stop (scalar_t__) ; 
 int /*<<< orphan*/  hb_buffer_list_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_dvd_close (scalar_t__*) ; 
 int /*<<< orphan*/  hb_dvd_stop (scalar_t__) ; 
 int /*<<< orphan*/  hb_stream_close (scalar_t__*) ; 

__attribute__((used)) static void reader_close( hb_work_object_t * w )
{
    hb_work_private_t * r = w->private_data;

    if ( r == NULL )
    {
        return;
    }
    if (r->bd)
    {
        hb_bd_stop( r->bd );
        hb_bd_close( &r->bd );
    }
    else if (r->dvd)
    {
        hb_dvd_stop( r->dvd );
        hb_dvd_close( &r->dvd );
    }
    else if (r->stream)
    {
        hb_stream_close(&r->stream);
    }

    int ii;
    for (ii = 0; ii < r->splice_list_size; ii++)
    {
        hb_buffer_list_close(&r->splice_list[ii].list);
    }

    free(r->fifos);
    free(r->splice_list);
    free(r);
}