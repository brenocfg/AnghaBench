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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

void ff_mjpeg_build_huffman_codes(uint8_t *huff_size, uint16_t *huff_code,
                                  const uint8_t *bits_table,
                                  const uint8_t *val_table)
{
    int i, j, k,nb, code, sym;

    /* Some badly encoded files [1] map 2 different codes to symbol 0.
       Only the first one is valid, so we zero-initialize this here and
       make sure we only set it once (the first time) in the loop below.

       [1]: Embedded JPEGs in "X7 RAW" and "X7 CinemaDNG" samples here:
            https://www.dji.com/gr/zenmuse-x7/info#downloads
     */
    huff_size[0] = 0;

    k = 0;
    code = 0;
    for(i=1;i<=16;i++) {
        nb = bits_table[i];
        for(j=0;j<nb;j++) {
            sym = val_table[k++];
            if (sym != 0 || huff_size[sym] == 0) { /* see comment above */
                huff_size[sym] = i;
                huff_code[sym] = code;
            }
            code++;
        }
        code <<= 1;
    }
}