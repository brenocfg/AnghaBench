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
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ FFABS (int) ; 
 int /*<<< orphan*/  FFMIN (int,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const unsigned char *seq_unpack_rle_block(const unsigned char *src,
                                                 const unsigned char *src_end,
                                                 unsigned char *dst, int dst_size)
{
    int i, len, sz;
    GetBitContext gb;
    int code_table[64];

    /* get the rle codes */
    init_get_bits(&gb, src, (src_end - src) * 8);
    for (i = 0, sz = 0; i < 64 && sz < dst_size; i++) {
        if (get_bits_left(&gb) < 4)
            return NULL;
        code_table[i] = get_sbits(&gb, 4);
        sz += FFABS(code_table[i]);
    }
    src += (get_bits_count(&gb) + 7) / 8;

    /* do the rle unpacking */
    for (i = 0; i < 64 && dst_size > 0; i++) {
        len = code_table[i];
        if (len < 0) {
            len = -len;
            if (src_end - src < 1)
                return NULL;
            memset(dst, *src++, FFMIN(len, dst_size));
        } else {
            if (src_end - src < len)
                return NULL;
            memcpy(dst, src, FFMIN(len, dst_size));
            src += len;
        }
        dst += len;
        dst_size -= len;
    }
    return src;
}