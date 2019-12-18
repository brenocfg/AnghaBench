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
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  DXVContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 
 int dxv_decompress_cgo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,unsigned int,int /*<<< orphan*/ **,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int dxv_decompress_opcodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int dxv_decompress_yo(DXVContext *ctx, GetByteContext *gb,
                             uint8_t *tex_data, int tex_size,
                             uint8_t *op_data, int max_op_size)
{
    int op_offset = bytestream2_get_le32(gb);
    unsigned op_size = bytestream2_get_le32(gb);
    int data_start = bytestream2_tell(gb);
    uint8_t *dst, *table0[256] = { 0 }, *table1[256] = { 0 };
    int ret, state = 0, skip, oi = 0, v, vv;

    if (op_offset < 8 || op_offset - 8 > bytestream2_get_bytes_left(gb))
        return AVERROR_INVALIDDATA;

    dst = tex_data;
    bytestream2_skip(gb, op_offset - 8);
    if (op_size > max_op_size)
        return AVERROR_INVALIDDATA;
    skip = dxv_decompress_opcodes(gb, op_data, op_size);
    if (skip < 0)
        return skip;
    bytestream2_seek(gb, data_start, SEEK_SET);

    v = bytestream2_get_le32(gb);
    AV_WL32(dst, v);
    vv = bytestream2_get_le32(gb);
    table0[0x9E3779B1 * (uint16_t)v >> 24] = dst;
    AV_WL32(dst + 4, vv);
    table1[0x9E3779B1 * (AV_RL32(dst + 2) & 0xFFFFFF) >> 24] = dst + 2;
    dst += 8;

    while (dst < tex_data + tex_size) {
        ret = dxv_decompress_cgo(ctx, gb, tex_data, tex_size, op_data, &oi, op_size,
                                 &dst, &state, table0, table1, 0);
        if (ret < 0)
            return ret;
    }

    bytestream2_seek(gb, data_start + op_offset + skip - 8, SEEK_SET);

    return 0;
}