#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int palette_set; scalar_t__ pts; int /*<<< orphan*/ * job; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_8__ {TYPE_1__* subtitle; TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_job_t ;
struct TYPE_6__ {int palette_set; scalar_t__* palette; } ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  hb_log (char*) ; 

int decsubInit( hb_work_object_t * w, hb_job_t * job )
{
    hb_work_private_t * pv;

    pv              = calloc( 1, sizeof( hb_work_private_t ) );
    w->private_data = pv;

    pv->job = job;
    pv->pts = 0;

    // Warn if the input color palette is empty
    pv->palette_set = w->subtitle->palette_set;
    if ( pv->palette_set )
    {
        // Make sure the entries in the palette are not all 0
        pv->palette_set = 0;
        int i;
        for (i=0; i<16; i++)
        {
            if (w->subtitle->palette[i])
            {
                pv->palette_set = 1;
                break;
            }
        }
    }
    if (!pv->palette_set) {
        hb_log( "decvobsub: input color palette is empty!" );
    }

    return 0;
}