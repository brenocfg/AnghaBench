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
typedef  size_t uint8_t ;
struct TYPE_3__ {int len; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ HuffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_huff_codes(uint8_t *src, uint8_t *dst, int dst_size,
                            int width, int height, HuffEntry *he)
{
    PutBitContext pb;
    int i, j;
    int count;

    init_put_bits(&pb, dst, dst_size);

    /* Write the codes */
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++)
            put_bits(&pb, he[src[i]].len, he[src[i]].code);

        src += width;
    }

    /* Pad output to a 32-bit boundary */
    count = put_bits_count(&pb) & 0x1F;

    if (count)
        put_bits(&pb, 32 - count, 0);

    /* Get the amount of bits written */
    count = put_bits_count(&pb);

    /* Flush the rest with zeroes */
    flush_put_bits(&pb);

    return count;
}