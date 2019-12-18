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
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  DXVContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int dxv_decompress_cgo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,unsigned int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int dxv_decompress_opcodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int dxv_decompress_cocg(DXVContext *ctx, GetByteContext *gb,
                               uint8_t *tex_data, int tex_size,
                               uint8_t *op_data0, uint8_t *op_data1,
                               int max_op_size0, int max_op_size1)
{
    uint8_t *dst, *tab2[256] = { 0 }, *tab0[256] = { 0 }, *tab3[256] = { 0 }, *tab1[256] = { 0 };
    int op_offset = bytestream2_get_le32(gb);
    unsigned op_size0 = bytestream2_get_le32(gb);
    unsigned op_size1 = bytestream2_get_le32(gb);
    int data_start = bytestream2_tell(gb);
    int skip0, skip1, oi0 = 0, oi1 = 0;
    int ret, state0 = 0, state1 = 0;

    if (op_offset < 12 || op_offset - 12 > bytestream2_get_bytes_left(gb))
        return AVERROR_INVALIDDATA;

    dst = tex_data;
    bytestream2_skip(gb, op_offset - 12);
    if (op_size0 > max_op_size0)
        return AVERROR_INVALIDDATA;
    skip0 = dxv_decompress_opcodes(gb, op_data0, op_size0);
    if (skip0 < 0)
        return skip0;
    if (op_size1 > max_op_size1)
        return AVERROR_INVALIDDATA;
    skip1 = dxv_decompress_opcodes(gb, op_data1, op_size1);
    if (skip1 < 0)
        return skip1;
    bytestream2_seek(gb, data_start, SEEK_SET);

    AV_WL32(dst, bytestream2_get_le32(gb));
    AV_WL32(dst + 4, bytestream2_get_le32(gb));
    AV_WL32(dst + 8, bytestream2_get_le32(gb));
    AV_WL32(dst + 12, bytestream2_get_le32(gb));

    tab0[0x9E3779B1 * AV_RL16(dst) >> 24] = dst;
    tab1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFF) >> 24] = dst + 2;
    tab2[0x9E3779B1 * AV_RL16(dst + 8) >> 24] = dst + 8;
    tab3[0x9E3779B1 * (AV_RL32(dst + 10) & 0xFFFFFF) >> 24] = dst + 10;
    dst += 16;
    while (dst + 10 < tex_data + tex_size) {
        ret = dxv_decompress_cgo(ctx, gb, tex_data, tex_size, op_data0, &oi0, op_size0,
                                 &dst, &state0, tab0, tab1, 8);
        if (ret < 0)
            return ret;
        ret = dxv_decompress_cgo(ctx, gb, tex_data, tex_size, op_data1, &oi1, op_size1,
                                 &dst, &state1, tab2, tab3, 8);
        if (ret < 0)
            return ret;
    }

    bytestream2_seek(gb, data_start - 12 + op_offset + skip0 + skip1, SEEK_SET);

    return 0;
}