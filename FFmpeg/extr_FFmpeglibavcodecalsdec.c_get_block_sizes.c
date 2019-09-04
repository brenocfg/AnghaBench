#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int block_switching; unsigned int frame_length; } ;
struct TYPE_5__ {unsigned int num_blocks; unsigned int cur_frame_length; TYPE_1__ sconf; int /*<<< orphan*/  gb; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ ALSSpecificConfig ;
typedef  TYPE_2__ ALSDecContext ;

/* Variables and functions */
 int get_bits_long (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  parse_bs_info (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int**,unsigned int*) ; 

__attribute__((used)) static void get_block_sizes(ALSDecContext *ctx, unsigned int *div_blocks,
                            uint32_t *bs_info)
{
    ALSSpecificConfig *sconf     = &ctx->sconf;
    GetBitContext *gb            = &ctx->gb;
    unsigned int *ptr_div_blocks = div_blocks;
    unsigned int b;

    if (sconf->block_switching) {
        unsigned int bs_info_len = 1 << (sconf->block_switching + 2);
        *bs_info = get_bits_long(gb, bs_info_len);
        *bs_info <<= (32 - bs_info_len);
    }

    ctx->num_blocks = 0;
    parse_bs_info(*bs_info, 0, 0, &ptr_div_blocks, &ctx->num_blocks);

    // The last frame may have an overdetermined block structure given in
    // the bitstream. In that case the defined block structure would need
    // more samples than available to be consistent.
    // The block structure is actually used but the block sizes are adapted
    // to fit the actual number of available samples.
    // Example: 5 samples, 2nd level block sizes: 2 2 2 2.
    // This results in the actual block sizes:    2 2 1 0.
    // This is not specified in 14496-3 but actually done by the reference
    // codec RM22 revision 2.
    // This appears to happen in case of an odd number of samples in the last
    // frame which is actually not allowed by the block length switching part
    // of 14496-3.
    // The ALS conformance files feature an odd number of samples in the last
    // frame.

    for (b = 0; b < ctx->num_blocks; b++)
        div_blocks[b] = ctx->sconf.frame_length >> div_blocks[b];

    if (ctx->cur_frame_length != ctx->sconf.frame_length) {
        unsigned int remaining = ctx->cur_frame_length;

        for (b = 0; b < ctx->num_blocks; b++) {
            if (remaining <= div_blocks[b]) {
                div_blocks[b] = remaining;
                ctx->num_blocks = b + 1;
                break;
            }

            remaining -= div_blocks[b];
        }
    }
}