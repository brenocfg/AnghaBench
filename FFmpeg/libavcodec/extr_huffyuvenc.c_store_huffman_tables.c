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
struct TYPE_4__ {int version; int alpha; int chroma; int /*<<< orphan*/ * len; int /*<<< orphan*/  vlc_n; int /*<<< orphan*/ * bits; int /*<<< orphan*/ * stats; } ;
typedef  TYPE_1__ HYuvContext ;

/* Variables and functions */
 int ff_huff_gen_len_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_huffyuv_generate_bits_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ store_table (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int store_huffman_tables(HYuvContext *s, uint8_t *buf)
{
    int i, ret;
    int size = 0;
    int count = 3;

    if (s->version > 2)
        count = 1 + s->alpha + 2*s->chroma;

    for (i = 0; i < count; i++) {
        if ((ret = ff_huff_gen_len_table(s->len[i], s->stats[i], s->vlc_n, 0)) < 0)
            return ret;

        if (ff_huffyuv_generate_bits_table(s->bits[i], s->len[i], s->vlc_n) < 0) {
            return -1;
        }

        size += store_table(s, s->len[i], buf + size);
    }
    return size;
}