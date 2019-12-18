#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_filter_private_t ;
struct TYPE_9__ {int /*<<< orphan*/ * private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
struct TYPE_8__ {int flags; } ;
struct TYPE_10__ {TYPE_1__ s; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 int HB_BUF_FLAG_EOF ; 
 int HB_FILTER_DONE ; 
 int HB_FILTER_OK ; 
 int /*<<< orphan*/  grayscale_filter (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int hb_grayscale_work( hb_filter_object_t * filter,
                              hb_buffer_t ** buf_in,
                              hb_buffer_t ** buf_out )
{
    hb_filter_private_t * pv = filter->private_data;
    hb_buffer_t * in = *buf_in;

    *buf_in = NULL;
    if (in->s.flags & HB_BUF_FLAG_EOF)
    {
        *buf_out = in;
        return HB_FILTER_DONE;
    }

    // Grayscale!
    grayscale_filter(pv, in);

    *buf_out = in;

    return HB_FILTER_OK;
}