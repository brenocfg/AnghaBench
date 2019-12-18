#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * block; } ;
typedef  TYPE_1__ HQContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int hq_decode_block (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_blocks (TYPE_1__*,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hq_decode_mb(HQContext *c, AVFrame *pic,
                        GetBitContext *gb, int x, int y)
{
    int qgroup, flag;
    int i, ret;

    qgroup = get_bits(gb, 4);
    flag = get_bits1(gb);

    for (i = 0; i < 8; i++) {
        ret = hq_decode_block(c, gb, c->block[i], qgroup, i >= 4, 0);
        if (ret < 0)
            return ret;
    }

    put_blocks(c, pic, 0, x,      y, flag, c->block[0], c->block[2]);
    put_blocks(c, pic, 0, x + 8,  y, flag, c->block[1], c->block[3]);
    put_blocks(c, pic, 2, x >> 1, y, flag, c->block[4], c->block[5]);
    put_blocks(c, pic, 1, x >> 1, y, flag, c->block[6], c->block[7]);

    return 0;
}