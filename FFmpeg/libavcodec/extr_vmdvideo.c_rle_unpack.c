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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WN16 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_get_bufferu (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_ne16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rle_unpack(const unsigned char *src, unsigned char *dest,
                      int src_count, int src_size, int dest_len)
{
    unsigned char *pd;
    int i, l, used = 0;
    unsigned char *dest_end = dest + dest_len;
    GetByteContext gb;
    uint16_t run_val;

    bytestream2_init(&gb, src, src_size);
    pd = dest;
    if (src_count & 1) {
        if (bytestream2_get_bytes_left(&gb) < 1)
            return 0;
        *pd++ = bytestream2_get_byteu(&gb);
        used++;
    }

    do {
        if (bytestream2_get_bytes_left(&gb) < 1)
            break;
        l = bytestream2_get_byteu(&gb);
        if (l & 0x80) {
            l = (l & 0x7F) * 2;
            if (dest_end - pd < l || bytestream2_get_bytes_left(&gb) < l)
                return bytestream2_tell(&gb);
            bytestream2_get_bufferu(&gb, pd, l);
            pd += l;
        } else {
            if (dest_end - pd < 2*l || bytestream2_get_bytes_left(&gb) < 2)
                return bytestream2_tell(&gb);
            run_val = bytestream2_get_ne16(&gb);
            for (i = 0; i < l; i++) {
                AV_WN16(pd, run_val);
                pd += 2;
            }
            l *= 2;
        }
        used += l;
    } while (used < src_count);

    return bytestream2_tell(&gb);
}