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
struct TYPE_5__ {int prev_poc_msb; int prev_poc_lsb; scalar_t__ prev_frame_num_offset; scalar_t__ prev_frame_num; } ;
struct TYPE_6__ {int /*<<< orphan*/ * last_pocs; TYPE_1__ poc; } ;
typedef  TYPE_2__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MIN ; 
 int MAX_DELAYED_PIC_COUNT ; 
 int /*<<< orphan*/  ff_h264_remove_all_refs (TYPE_2__*) ; 

__attribute__((used)) static void idr(H264Context *h)
{
    int i;
    ff_h264_remove_all_refs(h);
    h->poc.prev_frame_num        =
    h->poc.prev_frame_num_offset = 0;
    h->poc.prev_poc_msb          = 1<<16;
    h->poc.prev_poc_lsb          = -1;
    for (i = 0; i < MAX_DELAYED_PIC_COUNT; i++)
        h->last_pocs[i] = INT_MIN;
}