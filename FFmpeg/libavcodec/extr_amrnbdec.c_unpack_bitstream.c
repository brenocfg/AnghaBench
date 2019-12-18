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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  enum Mode { ____Placeholder_Mode } Mode ;
struct TYPE_3__ {int bad_frame_indicator; int /*<<< orphan*/  frame; } ;
typedef  int /*<<< orphan*/  AMRNBFrame ;
typedef  TYPE_1__ AMRContext ;

/* Variables and functions */
 int MODE_DTX ; 
 int NO_DATA ; 
 int N_MODES ; 
 int /*<<< orphan*/ * amr_unpacking_bitmaps_per_mode ; 
 int /*<<< orphan*/  ff_amr_bit_reorder (int /*<<< orphan*/ *,int,int const*,int /*<<< orphan*/ ) ; 
 int* frame_sizes_nb ; 

__attribute__((used)) static enum Mode unpack_bitstream(AMRContext *p, const uint8_t *buf,
                                  int buf_size)
{
    enum Mode mode;

    // Decode the first octet.
    mode = buf[0] >> 3 & 0x0F;                      // frame type
    p->bad_frame_indicator = (buf[0] & 0x4) != 0x4; // quality bit

    if (mode >= N_MODES || buf_size < frame_sizes_nb[mode] + 1) {
        return NO_DATA;
    }

    if (mode < MODE_DTX)
        ff_amr_bit_reorder((uint16_t *) &p->frame, sizeof(AMRNBFrame), buf + 1,
                           amr_unpacking_bitmaps_per_mode[mode]);

    return mode;
}