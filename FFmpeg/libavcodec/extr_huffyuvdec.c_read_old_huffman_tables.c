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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int bitstream_bpp; int /*<<< orphan*/ ** bits; int /*<<< orphan*/ ** len; int /*<<< orphan*/ * vlc; } ;
typedef  TYPE_1__ HYuvContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_BITS ; 
 int /*<<< orphan*/ * classic_add_chroma ; 
 int /*<<< orphan*/ * classic_add_luma ; 
 int /*<<< orphan*/  classic_shift_chroma ; 
 int classic_shift_chroma_table_size ; 
 int /*<<< orphan*/  classic_shift_luma ; 
 int classic_shift_luma_table_size ; 
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 int generate_joint_tables (TYPE_1__*) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int init_vlc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int read_len_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_old_huffman_tables(HYuvContext *s)
{
    GetBitContext gb;
    int i, ret;

    init_get_bits(&gb, classic_shift_luma,
                  classic_shift_luma_table_size * 8);
    if ((ret = read_len_table(s->len[0], &gb, 256)) < 0)
        return ret;

    init_get_bits(&gb, classic_shift_chroma,
                  classic_shift_chroma_table_size * 8);
    if ((ret = read_len_table(s->len[1], &gb, 256)) < 0)
        return ret;

    for (i = 0; i < 256; i++)
        s->bits[0][i] = classic_add_luma[i];
    for (i = 0; i < 256; i++)
        s->bits[1][i] = classic_add_chroma[i];

    if (s->bitstream_bpp >= 24) {
        memcpy(s->bits[1], s->bits[0], 256 * sizeof(uint32_t));
        memcpy(s->len[1], s->len[0], 256 * sizeof(uint8_t));
    }
    memcpy(s->bits[2], s->bits[1], 256 * sizeof(uint32_t));
    memcpy(s->len[2], s->len[1], 256 * sizeof(uint8_t));

    for (i = 0; i < 4; i++) {
        ff_free_vlc(&s->vlc[i]);
        if ((ret = init_vlc(&s->vlc[i], VLC_BITS, 256, s->len[i], 1, 1,
                            s->bits[i], 4, 4, 0)) < 0)
            return ret;
    }

    if ((ret = generate_joint_tables(s)) < 0)
        return ret;

    return 0;
}