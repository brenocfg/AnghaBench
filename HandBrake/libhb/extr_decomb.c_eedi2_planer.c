#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  eedi2_taskset; TYPE_4__** eedi_half; TYPE_2__** ref; int /*<<< orphan*/  tff; } ;
typedef  TYPE_5__ hb_filter_private_t ;
struct TYPE_10__ {TYPE_3__* plane; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__* plane; } ;
struct TYPE_7__ {int stride; int height; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t SRCPF ; 
 int /*<<< orphan*/  eedi2_fill_half_height_buffer_plane (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  taskset_cycle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void eedi2_planer( hb_filter_private_t * pv )
{
    /* Copy the first field from the source to a half-height frame. */
    int pp;
    for( pp = 0;  pp < 3; pp++ )
    {
        int pitch = pv->ref[1]->plane[pp].stride;
        int height = pv->ref[1]->plane[pp].height;
        int start_line = !pv->tff;

        eedi2_fill_half_height_buffer_plane(
                &pv->ref[1]->plane[pp].data[pitch * start_line],
                pv->eedi_half[SRCPF]->plane[pp].data, pitch, height );
    }

    /*
     * Now that all data is ready for our threads, fire them off
     * and wait for their completion.
     */
    taskset_cycle( &pv->eedi2_taskset );
}