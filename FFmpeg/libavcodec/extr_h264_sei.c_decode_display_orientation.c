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
struct TYPE_3__ {int present; int /*<<< orphan*/  anticlockwise_rotation; void* vflip; void* hflip; } ;
typedef  TYPE_1__ H264SEIDisplayOrientation ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ue_golomb_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_display_orientation(H264SEIDisplayOrientation *h,
                                      GetBitContext *gb)
{
    h->present = !get_bits1(gb);

    if (h->present) {
        h->hflip = get_bits1(gb);     // hor_flip
        h->vflip = get_bits1(gb);     // ver_flip

        h->anticlockwise_rotation = get_bits(gb, 16);
        get_ue_golomb_long(gb);       // display_orientation_repetition_period
        skip_bits1(gb);               // display_orientation_extension_flag
    }

    return 0;
}