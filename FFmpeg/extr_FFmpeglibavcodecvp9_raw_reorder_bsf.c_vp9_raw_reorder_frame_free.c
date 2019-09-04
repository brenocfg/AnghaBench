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
struct TYPE_4__ {int /*<<< orphan*/  packet; } ;
typedef  TYPE_1__ VP9RawReorderFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vp9_raw_reorder_frame_free(VP9RawReorderFrame **frame)
{
    if (*frame)
        av_packet_free(&(*frame)->packet);
    av_freep(frame);
}