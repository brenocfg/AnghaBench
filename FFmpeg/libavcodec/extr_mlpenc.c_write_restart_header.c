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
typedef  unsigned int uint8_t ;
typedef  unsigned int int32_t ;
struct TYPE_11__ {unsigned int timestamp; TYPE_1__* cur_restart_header; } ;
struct TYPE_10__ {int /*<<< orphan*/  buf; } ;
struct TYPE_9__ {unsigned int min_channel; unsigned int max_channel; unsigned int max_matrix_channel; unsigned int noise_shift; unsigned int noisegen_seed; unsigned int max_huff_lsbs; unsigned int max_output_bits; unsigned int data_check_present; int /*<<< orphan*/  lossless_check_data; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  TYPE_2__ PutBitContext ;
typedef  TYPE_3__ MLPEncodeContext ;

/* Variables and functions */
 unsigned int ff_mlp_restart_checksum (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_2__*) ; 
 int /*<<< orphan*/  put_bits (TYPE_2__*,int,unsigned int) ; 
 unsigned int put_bits_count (TYPE_2__*) ; 
 unsigned int xor_32_to_8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_restart_header(MLPEncodeContext *ctx, PutBitContext *pb)
{
    RestartHeader *rh = ctx->cur_restart_header;
    int32_t lossless_check = xor_32_to_8(rh->lossless_check_data);
    unsigned int start_count = put_bits_count(pb);
    PutBitContext tmpb;
    uint8_t checksum;
    unsigned int ch;

    put_bits(pb, 14, 0x31ea                ); /* TODO 0x31eb */
    put_bits(pb, 16, ctx->timestamp        );
    put_bits(pb,  4, rh->min_channel       );
    put_bits(pb,  4, rh->max_channel       );
    put_bits(pb,  4, rh->max_matrix_channel);
    put_bits(pb,  4, rh->noise_shift       );
    put_bits(pb, 23, rh->noisegen_seed     );
    put_bits(pb,  4, 0                     ); /* TODO max_shift */
    put_bits(pb,  5, rh->max_huff_lsbs     );
    put_bits(pb,  5, rh->max_output_bits   );
    put_bits(pb,  5, rh->max_output_bits   );
    put_bits(pb,  1, rh->data_check_present);
    put_bits(pb,  8, lossless_check        );
    put_bits(pb, 16, 0                     ); /* ignored */

    for (ch = 0; ch <= rh->max_matrix_channel; ch++)
        put_bits(pb, 6, ch);

    /* Data must be flushed for the checksum to be correct. */
    tmpb = *pb;
    flush_put_bits(&tmpb);

    checksum = ff_mlp_restart_checksum(pb->buf, put_bits_count(pb) - start_count);

    put_bits(pb,  8, checksum);
}