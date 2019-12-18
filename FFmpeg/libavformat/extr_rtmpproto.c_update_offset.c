#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flv_off; int flv_size; } ;
typedef  TYPE_1__ RTMPContext ;

/* Variables and functions */

__attribute__((used)) static int update_offset(RTMPContext *rt, int size)
{
    int old_flv_size;

    // generate packet header and put data into buffer for FLV demuxer
    if (rt->flv_off < rt->flv_size) {
        // There is old unread data in the buffer, thus append at the end
        old_flv_size  = rt->flv_size;
        rt->flv_size += size;
    } else {
        // All data has been read, write the new data at the start of the buffer
        old_flv_size = 0;
        rt->flv_size = size;
        rt->flv_off  = 0;
    }

    return old_flv_size;
}