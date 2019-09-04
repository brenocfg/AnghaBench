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
struct TYPE_3__ {int len; int code; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ HuffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int encode_slice(uint8_t *src, uint8_t *dst, int dst_size,
                        int width, int height, HuffEntry *he, int prediction)
{
    PutBitContext pb;
    int i, j;
    int count;

    init_put_bits(&pb, dst, dst_size);

    put_bits(&pb, 8, 0);
    put_bits(&pb, 8, prediction);

    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            const int idx = src[i];
            put_bits(&pb, he[idx].len, he[idx].code);
        }

        src += width;
    }

    count = put_bits_count(&pb) & 0x1F;

    if (count)
        put_bits(&pb, 32 - count, 0);

    count = put_bits_count(&pb);

    flush_put_bits(&pb);

    return count >> 3;
}