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
struct TYPE_4__ {int version; int alpha; int chroma; int /*<<< orphan*/ * bits; int /*<<< orphan*/ * len; int /*<<< orphan*/  vlc_n; int /*<<< orphan*/ * vlc; } ;
typedef  TYPE_1__ HYuvContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_BITS ; 
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 int ff_huffyuv_generate_bits_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int generate_joint_tables (TYPE_1__*) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int init_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int read_len_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_huffman_tables(HYuvContext *s, const uint8_t *src, int length)
{
    GetBitContext gb;
    int i, ret;
    int count = 3;

    if ((ret = init_get_bits(&gb, src, length * 8)) < 0)
        return ret;

    if (s->version > 2)
        count = 1 + s->alpha + 2*s->chroma;

    for (i = 0; i < count; i++) {
        if ((ret = read_len_table(s->len[i], &gb, s->vlc_n)) < 0)
            return ret;
        if ((ret = ff_huffyuv_generate_bits_table(s->bits[i], s->len[i], s->vlc_n)) < 0)
            return ret;
        ff_free_vlc(&s->vlc[i]);
        if ((ret = init_vlc(&s->vlc[i], VLC_BITS, s->vlc_n, s->len[i], 1, 1,
                           s->bits[i], 4, 4, 0)) < 0)
            return ret;
    }

    if ((ret = generate_joint_tables(s)) < 0)
        return ret;

    return (get_bits_count(&gb) + 7) / 8;
}