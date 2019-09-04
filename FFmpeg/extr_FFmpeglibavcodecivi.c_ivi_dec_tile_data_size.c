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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ivi_dec_tile_data_size(GetBitContext *gb)
{
    int    len;

    len = 0;
    if (get_bits1(gb)) {
        len = get_bits(gb, 8);
        if (len == 255)
            len = get_bits_long(gb, 24);
    }

    /* align the bitstream reader on the byte boundary */
    align_get_bits(gb);

    return len;
}