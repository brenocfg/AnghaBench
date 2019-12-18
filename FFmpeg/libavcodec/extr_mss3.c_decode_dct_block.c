#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
struct TYPE_4__ {int got_error; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  int /*<<< orphan*/  DCTBlockCoder ;

/* Variables and functions */
 scalar_t__ decode_dct (TYPE_1__*,int /*<<< orphan*/ *,int*,int,int) ; 
 int /*<<< orphan*/  ff_mss34_dct_put (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void decode_dct_block(RangeCoder *c, DCTBlockCoder *bc,
                             uint8_t *dst, ptrdiff_t stride, int block_size,
                             int *block, int mb_x, int mb_y)
{
    int i, j;
    int bx, by;
    int nblocks = block_size >> 3;

    bx = mb_x * nblocks;
    by = mb_y * nblocks;

    for (j = 0; j < nblocks; j++) {
        for (i = 0; i < nblocks; i++) {
            if (decode_dct(c, bc, block, bx + i, by + j)) {
                c->got_error = 1;
                return;
            }
            ff_mss34_dct_put(dst + i * 8, stride, block);
        }
        dst += 8 * stride;
    }
}