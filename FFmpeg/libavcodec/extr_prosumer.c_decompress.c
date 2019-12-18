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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_WN16 (int*,int /*<<< orphan*/ ) ; 
 int PAIR (int,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left_p (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_eof (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_peek_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_put_le16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_put_le32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decompress(GetByteContext *gb, int size, PutByteContext *pb, const uint32_t *lut)
{
    int pos, idx, cnt, fill;
    uint32_t a, b, c;

    bytestream2_skip(gb, 32);
    cnt = 4;
    a = bytestream2_get_le32(gb);
    idx = a >> 20;
    b = lut[2 * idx];

    while (1) {
        if (bytestream2_get_bytes_left_p(pb) <= 0 || bytestream2_get_eof(pb))
            return 0;
        if ((b & 0xFF00u) != 0x8000u || (b & 0xFFu)) {
            if ((b & 0xFF00u) != 0x8000u) {
                bytestream2_put_le16(pb, b);
            } else {
                idx = 0;
                for (int i = 0; i < (b & 0xFFu); i++)
                    bytestream2_put_le32(pb, 0);
            }
            c = b >> 16;
            if (c & 0xFF00u) {
                fill = lut[2 * idx + 1];
                if ((c & 0xF000u) == 0x1000) {
                    bytestream2_put_le16(pb, fill);
                } else {
                    bytestream2_put_le32(pb, fill);
                }
                c = (c >> 8) & 0x0Fu;
            }
            while (c) {
                a <<= 4;
                cnt--;
                if (!cnt) {
                    if (bytestream2_get_bytes_left(gb) <= 0) {
                        if (!a)
                            return 0;
                    } else {
                        pos = bytestream2_tell(gb);
                        bytestream2_seek(gb, pos ^ 2, SEEK_SET);
                        AV_WN16(&a, bytestream2_peek_le16(gb));
                        bytestream2_seek(gb, pos + 2, SEEK_SET);
                    }
                    cnt = 4;
                }
                c--;
            }
            idx = a >> 20;
            b = lut[2 * idx];
            if (!b)
                return AVERROR_INVALIDDATA;
            continue;
        }
        idx = 2;
        while (idx) {
            a <<= 4;
            cnt--;
            if (cnt) {
                idx--;
                continue;
            }
            if (bytestream2_get_bytes_left(gb) <= 0) {
                if (a) {
                    cnt = 4;
                    idx--;
                    continue;
                }
                return 0;
            }
            pos = bytestream2_tell(gb);
            bytestream2_seek(gb, pos ^ 2, SEEK_SET);
            AV_WN16(&a, bytestream2_peek_le16(gb));
            bytestream2_seek(gb, pos + 2, SEEK_SET);
            cnt = 4;
            idx--;
        }
        b = PAIR(4, a) >> 16;
    }

    return 0;
}