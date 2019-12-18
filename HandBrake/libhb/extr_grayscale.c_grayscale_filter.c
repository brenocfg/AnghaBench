#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int cpu_count; int /*<<< orphan*/  grayscale_taskset; TYPE_1__* grayscale_arguments; } ;
typedef  TYPE_2__ hb_filter_private_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
struct TYPE_4__ {int /*<<< orphan*/ * src; } ;

/* Variables and functions */
 int /*<<< orphan*/  taskset_cycle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void grayscale_filter( hb_filter_private_t * pv,
                              hb_buffer_t         * in )
{

    int segment;

    for( segment = 0; segment < pv->cpu_count; segment++ )
    {
        /*
         * Setup the work for this plane.
         */
        pv->grayscale_arguments[segment].src = in;
    }

    /*
     * Allow the taskset threads to make one pass over the data.
     */
    taskset_cycle( &pv->grayscale_taskset );

    /*
     * Entire frame is now grayed.
     */
}