#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_align_put_bits (int /*<<< orphan*/ *) ; 
 int ff_pce_copy_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ff_copy_pce_data(PutBitContext *pb, GetBitContext *gb)
{
    int five_bit_ch, four_bit_ch, comment_size, bits;
    int offset = put_bits_count(pb);

    ff_pce_copy_bits(pb, gb, 10);               // Tag, Object Type, Frequency
    five_bit_ch  = ff_pce_copy_bits(pb, gb, 4); // Front
    five_bit_ch += ff_pce_copy_bits(pb, gb, 4); // Side
    five_bit_ch += ff_pce_copy_bits(pb, gb, 4); // Back
    four_bit_ch  = ff_pce_copy_bits(pb, gb, 2); // LFE
    four_bit_ch += ff_pce_copy_bits(pb, gb, 3); // Data
    five_bit_ch += ff_pce_copy_bits(pb, gb, 4); // Coupling
    if (ff_pce_copy_bits(pb, gb, 1))            // Mono Mixdown
        ff_pce_copy_bits(pb, gb, 4);
    if (ff_pce_copy_bits(pb, gb, 1))            // Stereo Mixdown
        ff_pce_copy_bits(pb, gb, 4);
    if (ff_pce_copy_bits(pb, gb, 1))            // Matrix Mixdown
        ff_pce_copy_bits(pb, gb, 3);
    for (bits = five_bit_ch*5+four_bit_ch*4; bits > 16; bits -= 16)
        ff_pce_copy_bits(pb, gb, 16);
    if (bits)
        ff_pce_copy_bits(pb, gb, bits);
    avpriv_align_put_bits(pb);
    align_get_bits(gb);
    comment_size = ff_pce_copy_bits(pb, gb, 8);
    for (; comment_size > 0; comment_size--)
        ff_pce_copy_bits(pb, gb, 8);

    return put_bits_count(pb) - offset;
}