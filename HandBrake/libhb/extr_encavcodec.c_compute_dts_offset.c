#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ frameno_in; int /*<<< orphan*/  dts_delay; TYPE_3__* job; } ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_8__ {int /*<<< orphan*/  start; } ;
struct TYPE_12__ {TYPE_1__ s; } ;
typedef  TYPE_5__ hb_buffer_t ;
struct TYPE_9__ {int /*<<< orphan*/  init_delay; } ;
struct TYPE_10__ {scalar_t__ areBframes; TYPE_2__ config; } ;

/* Variables and functions */

__attribute__((used)) static void compute_dts_offset( hb_work_private_t * pv, hb_buffer_t * buf )
{
    if ( pv->job->areBframes )
    {
        if ( ( pv->frameno_in ) == pv->job->areBframes )
        {
            pv->dts_delay = buf->s.start;
            pv->job->config.init_delay = pv->dts_delay;
        }
    }
}