#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {size_t* permutated; } ;
struct TYPE_7__ {int** block; int /*<<< orphan*/  factor; TYPE_1__ intra_scantable; } ;
typedef  TYPE_2__ IMM4Context ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int decode_block (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,unsigned int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decode_blocks(AVCodecContext *avctx, GetBitContext *gb,
                         unsigned cbp, int flag, int offset, unsigned flag2)
{
    IMM4Context *s = avctx->priv_data;
    const uint8_t *scantable = s->intra_scantable.permutated;
    int ret, i;

    memset(s->block, 0, sizeof(s->block));

    for (i = 0; i < 6; i++) {
        if (!flag) {
            int x = get_bits(gb, 8);

            if (x == 255)
                x = 128;
            x *= 8;

            s->block[i][scantable[0]] = x;
        }

        if (cbp & (1 << (5 - i))) {
            ret = decode_block(avctx, gb, i, s->factor, flag, offset, flag2);
            if (ret < 0)
                return ret;
        }
    }

    return 0;
}