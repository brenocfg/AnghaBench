#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {int buf; } ;
typedef  TYPE_1__ PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  encode_ac_coeffs (TYPE_1__*,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  encode_dc_coeffs (TYPE_1__*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_1__*) ; 
 int /*<<< orphan*/  init_put_bits (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int put_bits_ptr (TYPE_1__*) ; 

__attribute__((used)) static int encode_slice_plane(int16_t *blocks, int mb_count, uint8_t *buf, unsigned buf_size, int *qmat, int sub_sample_chroma,
                              const uint8_t ff_prores_scan[64])
{
    int blocks_per_slice;
    PutBitContext pb;

    blocks_per_slice = mb_count << (2 - sub_sample_chroma);
    init_put_bits(&pb, buf, buf_size);

    encode_dc_coeffs(&pb, blocks, blocks_per_slice, qmat);
    encode_ac_coeffs(&pb, blocks, blocks_per_slice, qmat, ff_prores_scan);

    flush_put_bits(&pb);
    return put_bits_ptr(&pb) - pb.buf;
}