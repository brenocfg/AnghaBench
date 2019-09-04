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
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_memcpy_backptr (int*,int,int) ; 
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int*,int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int const*,int) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xan_unpack(uint8_t *dest, int dest_len,
                       const uint8_t *src, int src_len)
{
    uint8_t opcode;
    int size;
    uint8_t *dest_org = dest;
    uint8_t *dest_end = dest + dest_len;
    GetByteContext ctx;

    bytestream2_init(&ctx, src, src_len);
    while (dest < dest_end && bytestream2_get_bytes_left(&ctx)) {
        opcode = bytestream2_get_byte(&ctx);

        if (opcode < 0xe0) {
            int size2, back;
            if ((opcode & 0x80) == 0) {
                size = opcode & 3;

                back  = ((opcode & 0x60) << 3) + bytestream2_get_byte(&ctx) + 1;
                size2 = ((opcode & 0x1c) >> 2) + 3;
            } else if ((opcode & 0x40) == 0) {
                size = bytestream2_peek_byte(&ctx) >> 6;

                back  = (bytestream2_get_be16(&ctx) & 0x3fff) + 1;
                size2 = (opcode & 0x3f) + 4;
            } else {
                size = opcode & 3;

                back  = ((opcode & 0x10) << 12) + bytestream2_get_be16(&ctx) + 1;
                size2 = ((opcode & 0x0c) <<  6) + bytestream2_get_byte(&ctx) + 5;
            }

            if (dest_end - dest < size + size2 ||
                dest + size - dest_org < back ||
                bytestream2_get_bytes_left(&ctx) < size)
                return;
            bytestream2_get_buffer(&ctx, dest, size);
            dest += size;
            av_memcpy_backptr(dest, back, size2);
            dest += size2;
        } else {
            int finish = opcode >= 0xfc;
            size = finish ? opcode & 3 : ((opcode & 0x1f) << 2) + 4;

            if (dest_end - dest < size || bytestream2_get_bytes_left(&ctx) < size)
                return;
            bytestream2_get_buffer(&ctx, dest, size);
            dest += size;
            if (finish)
                return;
        }
    }
}