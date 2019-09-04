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
struct TYPE_3__ {int present; int arrangement_type; void* arrangement_repetition_period; void* quincunx_sampling_flag; void* current_frame_is_frame0_flag; void* content_interpretation_type; void* arrangement_cancel_flag; void* arrangement_id; } ;
typedef  TYPE_1__ H264SEIFramePacking ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 void* get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_frame_packing_arrangement(H264SEIFramePacking *h,
                                            GetBitContext *gb)
{
    h->arrangement_id          = get_ue_golomb_long(gb);
    h->arrangement_cancel_flag = get_bits1(gb);
    h->present = !h->arrangement_cancel_flag;

    if (h->present) {
        h->arrangement_type = get_bits(gb, 7);
        h->quincunx_sampling_flag         = get_bits1(gb);
        h->content_interpretation_type    = get_bits(gb, 6);

        // spatial_flipping_flag, frame0_flipped_flag, field_views_flag
        skip_bits(gb, 3);
        h->current_frame_is_frame0_flag = get_bits1(gb);
        // frame0_self_contained_flag, frame1_self_contained_flag
        skip_bits(gb, 2);

        if (!h->quincunx_sampling_flag && h->arrangement_type != 5)
            skip_bits(gb, 16);      // frame[01]_grid_position_[xy]
        skip_bits(gb, 8);           // frame_packing_arrangement_reserved_byte
        h->arrangement_repetition_period = get_ue_golomb_long(gb);
    }
    skip_bits1(gb);                 // frame_packing_arrangement_extension_flag

    return 0;
}