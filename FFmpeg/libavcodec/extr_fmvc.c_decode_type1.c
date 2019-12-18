#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ buffer_start; scalar_t__ buffer_end; } ;
typedef  TYPE_1__ PutByteContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_put_byte (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bytestream2_put_le32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int bytestream2_tell_p (TYPE_1__*) ; 

__attribute__((used)) static int decode_type1(GetByteContext *gb, PutByteContext *pb)
{
    unsigned opcode = 0, len;
    int high = 0;
    int i, pos;

    while (bytestream2_get_bytes_left(gb) > 0) {
        GetByteContext gbc;

        while (bytestream2_get_bytes_left(gb) > 0) {
            while (bytestream2_get_bytes_left(gb) > 0) {
                opcode = bytestream2_get_byte(gb);
                high = opcode >= 0x20;
                if (high)
                    break;
                if (opcode)
                    break;
                opcode = bytestream2_get_byte(gb);
                if (opcode < 0xF8) {
                    opcode += 32;
                    break;
                }
                i = opcode - 0xF8;
                if (i) {
                    len = 256;
                    do {
                        len *= 2;
                        --i;
                    } while (i);
                } else {
                    len = 280;
                }
                do {
                    bytestream2_put_le32(pb, bytestream2_get_le32(gb));
                    bytestream2_put_le32(pb, bytestream2_get_le32(gb));
                    len -= 8;
                } while (len && bytestream2_get_bytes_left(gb) > 0);
            }

            if (!high) {
                do {
                    bytestream2_put_byte(pb, bytestream2_get_byte(gb));
                    --opcode;
                } while (opcode && bytestream2_get_bytes_left(gb) > 0);

                while (bytestream2_get_bytes_left(gb) > 0) {
                    GetByteContext gbc;

                    opcode = bytestream2_get_byte(gb);
                    if (opcode >= 0x20)
                        break;
                    bytestream2_init(&gbc, pb->buffer_start, pb->buffer_end - pb->buffer_start);

                    pos = -(opcode | 32 * bytestream2_get_byte(gb)) - 1;
                    bytestream2_seek(&gbc, bytestream2_tell_p(pb) + pos, SEEK_SET);
                    bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
                    bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
                    bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
                    bytestream2_put_byte(pb, bytestream2_get_byte(gb));
                }
            }
            high = 0;
            if (opcode < 0x40)
                break;
            bytestream2_init(&gbc, pb->buffer_start, pb->buffer_end - pb->buffer_start);
            pos = (-((opcode & 0x1F) | 32 * bytestream2_get_byte(gb)) - 1);
            bytestream2_seek(&gbc, bytestream2_tell_p(pb) + pos, SEEK_SET);
            bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
            bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
            len = (opcode >> 5) - 1;
            do {
                bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
                --len;
            } while (len && bytestream2_get_bytes_left(&gbc) > 0);
        }
        len = opcode & 0x1F;
        if (!len) {
            if (!bytestream2_peek_byte(gb)) {
                do {
                    bytestream2_skip(gb, 1);
                    len += 255;
                } while (!bytestream2_peek_byte(gb) && bytestream2_get_bytes_left(gb) > 0);
            }
            len += bytestream2_get_byte(gb) + 31;
        }
        pos = -bytestream2_get_byte(gb);
        bytestream2_init(&gbc, pb->buffer_start, pb->buffer_end - pb->buffer_start);
        bytestream2_seek(&gbc, bytestream2_tell_p(pb) + pos - (bytestream2_get_byte(gb) << 8), SEEK_SET);
        if (bytestream2_tell_p(pb) == bytestream2_tell(&gbc))
            break;
        if (len < 5 || bytestream2_tell_p(pb) - bytestream2_tell(&gbc) < 4) {
            bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
            bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
            bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
        } else {
            bytestream2_put_le32(pb, bytestream2_get_le32(&gbc));
            len--;
        }
        do {
            bytestream2_put_byte(pb, bytestream2_get_byte(&gbc));
            len--;
        } while (len && bytestream2_get_bytes_left(&gbc) > 0);
    }

    return 0;
}