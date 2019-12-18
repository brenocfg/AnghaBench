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
struct TYPE_4__ {int chroma_format; scalar_t__ swap_uv; int /*<<< orphan*/ ** pblocks; int /*<<< orphan*/ * block; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  exchange_uv (TYPE_1__*) ; 

void ff_xvmc_pack_pblocks(MpegEncContext *s, int cbp)
{
    int i, j = 0;
    const int mb_block_count = 4 + (1 << s->chroma_format);

    cbp <<= 12-mb_block_count;
    for (i = 0; i < mb_block_count; i++) {
        if (cbp & (1 << 11))
            s->pblocks[i] = &s->block[j++];
        else
            s->pblocks[i] = NULL;
        cbp += cbp;
    }
    if (s->swap_uv) {
        exchange_uv(s);
    }
}