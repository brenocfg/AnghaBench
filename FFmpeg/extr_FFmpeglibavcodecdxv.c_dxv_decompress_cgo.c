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
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  DXVContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RL16 (int*) ; 
 int AV_RL32 (int*) ; 
 int /*<<< orphan*/  AV_WL16 (int*,int) ; 
 int /*<<< orphan*/  AV_WL32 (int*,int) ; 
 size_t bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dxv_decompress_cgo(DXVContext *ctx, GetByteContext *gb,
                              uint8_t *tex_data, int tex_size,
                              uint8_t *op_data, int *oindex,
                              int op_size,
                              uint8_t **dstp, int *statep,
                              uint8_t **tab0, uint8_t **tab1,
                              int offset)
{
    uint8_t *dst = *dstp;
    uint8_t *tptr0, *tptr1, *tptr3;
    int oi = *oindex;
    int state = *statep;
    int opcode, v, vv;

    if (state <= 0) {
        if (oi >= op_size)
            return AVERROR_INVALIDDATA;
        opcode = op_data[oi++];
        if (!opcode) {
            v = bytestream2_get_byte(gb);
            if (v == 255) {
                do {
                    if (bytestream2_get_bytes_left(gb) <= 0)
                        return AVERROR_INVALIDDATA;
                    opcode = bytestream2_get_le16(gb);
                    v += opcode;
                } while (opcode == 0xFFFF);
            }
            AV_WL32(dst, AV_RL32(dst - (8 + offset)));
            AV_WL32(dst + 4, AV_RL32(dst - (4 + offset)));
            state = v + 4;
            goto done;
        }

        switch (opcode) {
        case 1:
            AV_WL32(dst, AV_RL32(dst - (8 + offset)));
            AV_WL32(dst + 4, AV_RL32(dst - (4 + offset)));
            break;
        case 2:
            vv = (8 + offset) * (bytestream2_get_le16(gb) + 1);
            if (vv < 0 || vv > dst - tex_data)
                return AVERROR_INVALIDDATA;
            tptr0 = dst - vv;
            v = AV_RL32(tptr0);
            AV_WL32(dst, AV_RL32(tptr0));
            AV_WL32(dst + 4, AV_RL32(tptr0 + 4));
            tab0[0x9E3779B1 * (uint16_t)v >> 24] = dst;
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 3:
            AV_WL32(dst, bytestream2_get_le32(gb));
            AV_WL32(dst + 4, bytestream2_get_le32(gb));
            tab0[0x9E3779B1 * AV_RL16(dst) >> 24] = dst;
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 4:
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, bytestream2_get_le16(gb));
            AV_WL16(dst + 2, AV_RL16(tptr3));
            dst[4] = tptr3[2];
            AV_WL16(dst + 5, bytestream2_get_le16(gb));
            dst[7] = bytestream2_get_byte(gb);
            tab0[0x9E3779B1 * AV_RL16(dst) >> 24] = dst;
            break;
        case 5:
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, bytestream2_get_le16(gb));
            AV_WL16(dst + 2, bytestream2_get_le16(gb));
            dst[4] = bytestream2_get_byte(gb);
            AV_WL16(dst + 5, AV_RL16(tptr3));
            dst[7] = tptr3[2];
            tab0[0x9E3779B1 * AV_RL16(dst) >> 24] = dst;
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 6:
            tptr0 = tab1[bytestream2_get_byte(gb)];
            if (!tptr0)
                return AVERROR_INVALIDDATA;
            tptr1 = tab1[bytestream2_get_byte(gb)];
            if (!tptr1)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, bytestream2_get_le16(gb));
            AV_WL16(dst + 2, AV_RL16(tptr0));
            dst[4] = tptr0[2];
            AV_WL16(dst + 5, AV_RL16(tptr1));
            dst[7] = tptr1[2];
            tab0[0x9E3779B1 * AV_RL16(dst) >> 24] = dst;
            break;
        case 7:
            v = (8 + offset) * (bytestream2_get_le16(gb) + 1);
            if (v < 0 || v > dst - tex_data)
                return AVERROR_INVALIDDATA;
            tptr0 = dst - v;
            AV_WL16(dst, bytestream2_get_le16(gb));
            AV_WL16(dst + 2, AV_RL16(tptr0 + 2));
            AV_WL32(dst + 4, AV_RL32(tptr0 + 4));
            tab0[0x9E3779B1 * AV_RL16(dst) >> 24] = dst;
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 8:
            tptr1 = tab0[bytestream2_get_byte(gb)];
            if (!tptr1)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(tptr1));
            AV_WL16(dst + 2, bytestream2_get_le16(gb));
            AV_WL32(dst + 4, bytestream2_get_le32(gb));
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 9:
            tptr1 = tab0[bytestream2_get_byte(gb)];
            if (!tptr1)
                return AVERROR_INVALIDDATA;
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(tptr1));
            AV_WL16(dst + 2, AV_RL16(tptr3));
            dst[4] = tptr3[2];
            AV_WL16(dst + 5, bytestream2_get_le16(gb));
            dst[7] = bytestream2_get_byte(gb);
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 10:
            tptr1 = tab0[bytestream2_get_byte(gb)];
            if (!tptr1)
                return AVERROR_INVALIDDATA;
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(tptr1));
            AV_WL16(dst + 2, bytestream2_get_le16(gb));
            dst[4] = bytestream2_get_byte(gb);
            AV_WL16(dst + 5, AV_RL16(tptr3));
            dst[7] = tptr3[2];
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 11:
            tptr0 = tab0[bytestream2_get_byte(gb)];
            if (!tptr0)
                return AVERROR_INVALIDDATA;
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            tptr1 = tab1[bytestream2_get_byte(gb)];
            if (!tptr1)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(tptr0));
            AV_WL16(dst + 2, AV_RL16(tptr3));
            dst[4] = tptr3[2];
            AV_WL16(dst + 5, AV_RL16(tptr1));
            dst[7] = tptr1[2];
            break;
        case 12:
            tptr1 = tab0[bytestream2_get_byte(gb)];
            if (!tptr1)
                return AVERROR_INVALIDDATA;
            v = (8 + offset) * (bytestream2_get_le16(gb) + 1);
            if (v < 0 || v > dst - tex_data)
                return AVERROR_INVALIDDATA;
            tptr0 = dst - v;
            AV_WL16(dst, AV_RL16(tptr1));
            AV_WL16(dst + 2, AV_RL16(tptr0 + 2));
            AV_WL32(dst + 4, AV_RL32(tptr0 + 4));
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 13:
            AV_WL16(dst, AV_RL16(dst - (8 + offset)));
            AV_WL16(dst + 2, bytestream2_get_le16(gb));
            AV_WL32(dst + 4, bytestream2_get_le32(gb));
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 14:
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(dst - (8 + offset)));
            AV_WL16(dst + 2, AV_RL16(tptr3));
            dst[4] = tptr3[2];
            AV_WL16(dst + 5, bytestream2_get_le16(gb));
            dst[7] = bytestream2_get_byte(gb);
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 15:
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(dst - (8 + offset)));
            AV_WL16(dst + 2, bytestream2_get_le16(gb));
            dst[4] = bytestream2_get_byte(gb);
            AV_WL16(dst + 5, AV_RL16(tptr3));
            dst[7] = tptr3[2];
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        case 16:
            tptr3 = tab1[bytestream2_get_byte(gb)];
            if (!tptr3)
                return AVERROR_INVALIDDATA;
            tptr1 = tab1[bytestream2_get_byte(gb)];
            if (!tptr1)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(dst - (8 + offset)));
            AV_WL16(dst + 2, AV_RL16(tptr3));
            dst[4] = tptr3[2];
            AV_WL16(dst + 5, AV_RL16(tptr1));
            dst[7] = tptr1[2];
            break;
        case 17:
            v = (8 + offset) * (bytestream2_get_le16(gb) + 1);
            if (v < 0 || v > dst - tex_data)
                return AVERROR_INVALIDDATA;
            AV_WL16(dst, AV_RL16(dst - (8 + offset)));
            AV_WL16(dst + 2, AV_RL16(&dst[-v + 2]));
            AV_WL32(dst + 4, AV_RL32(&dst[-v + 4]));
            tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFFu) >> 24] = dst + 2;
            break;
        default:
            break;
        }
    } else {
done:
        AV_WL32(dst, AV_RL32(dst - (8 + offset)));
        AV_WL32(dst + 4, AV_RL32(dst - (4 + offset)));
        state--;
    }
    if (dst - tex_data + 8 > tex_size)
        return AVERROR_INVALIDDATA;
    dst += 8;

    *oindex = oi;
    *dstp = dst;
    *statep = state;

    return 0;
}