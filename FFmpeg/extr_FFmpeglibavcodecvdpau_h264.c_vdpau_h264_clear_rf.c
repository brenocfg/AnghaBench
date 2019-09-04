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
struct TYPE_3__ {scalar_t__ frame_idx; scalar_t__* field_order_cnt; void* bottom_is_reference; void* top_is_reference; void* is_long_term; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ VdpReferenceFrameH264 ;

/* Variables and functions */
 void* VDP_FALSE ; 
 int /*<<< orphan*/  VDP_INVALID_HANDLE ; 

__attribute__((used)) static void vdpau_h264_clear_rf(VdpReferenceFrameH264 *rf)
{
    rf->surface             = VDP_INVALID_HANDLE;
    rf->is_long_term        = VDP_FALSE;
    rf->top_is_reference    = VDP_FALSE;
    rf->bottom_is_reference = VDP_FALSE;
    rf->field_order_cnt[0]  = 0;
    rf->field_order_cnt[1]  = 0;
    rf->frame_idx           = 0;
}