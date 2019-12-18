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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 

__attribute__((used)) static int cin_decode_huffman(const unsigned char *src, int src_size,
                              unsigned char *dst, int dst_size)
{
    int b, huff_code = 0;
    unsigned char huff_code_table[15];
    unsigned char *dst_cur       = dst;
    unsigned char *dst_end       = dst + dst_size;
    const unsigned char *src_end = src + src_size;

    memcpy(huff_code_table, src, 15);
    src += 15;

    while (src < src_end) {
        huff_code = *src++;
        if ((huff_code >> 4) == 15) {
            b          = huff_code << 4;
            huff_code  = *src++;
            *dst_cur++ = b | (huff_code >> 4);
        } else
            *dst_cur++ = huff_code_table[huff_code >> 4];
        if (dst_cur >= dst_end)
            break;

        huff_code &= 15;
        if (huff_code == 15) {
            *dst_cur++ = *src++;
        } else
            *dst_cur++ = huff_code_table[huff_code];
        if (dst_cur >= dst_end)
            break;
    }

    return dst_cur - dst;
}