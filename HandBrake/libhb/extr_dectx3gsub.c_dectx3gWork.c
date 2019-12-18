#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_work_private_t ;
struct TYPE_10__ {int /*<<< orphan*/ * private_data; } ;
typedef  TYPE_2__ hb_work_object_t ;
struct TYPE_9__ {scalar_t__ stop; int flags; } ;
struct TYPE_11__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_WORK_DONE ; 
 int HB_WORK_OK ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 TYPE_3__* tx3g_decode_to_ssa (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int dectx3gWork( hb_work_object_t * w, hb_buffer_t ** buf_in,
                        hb_buffer_t ** buf_out )
{
    hb_work_private_t * pv = w->private_data;
    hb_buffer_t * in = *buf_in;

    if ( in->s.stop == 0 ) {
        hb_log( "dectx3gsub: subtitle packet lacks duration" );
    }

    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_out = in;
        *buf_in = NULL;
        return HB_WORK_DONE;
    }

    *buf_out = tx3g_decode_to_ssa(pv, in);

    return HB_WORK_OK;
}