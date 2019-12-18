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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  VLC ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int ff_init_vlc_sparse (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int,int,int*,int,int,int*,int,int,int) ; 
 int /*<<< orphan*/  ff_mjpeg_build_huffman_codes (int /*<<< orphan*/ *,int*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int build_vlc(VLC *vlc, const uint8_t *bits_table,
                     const uint8_t *val_table, int nb_codes,
                     int use_static, int is_ac)
{
    uint8_t huff_size[256] = { 0 };
    uint16_t huff_code[256];
    uint16_t huff_sym[256];
    int i;

    av_assert0(nb_codes <= 256);

    ff_mjpeg_build_huffman_codes(huff_size, huff_code, bits_table, val_table);

    for (i = 0; i < 256; i++)
        huff_sym[i] = i + 16 * is_ac;

    if (is_ac)
        huff_sym[0] = 16 * 256;

    return ff_init_vlc_sparse(vlc, 9, nb_codes, huff_size, 1, 1,
                              huff_code, 2, 2, huff_sym, 2, 2, use_static);
}