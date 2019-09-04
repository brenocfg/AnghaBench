#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int64_t ;
struct TYPE_9__ {scalar_t__ buffer; } ;
struct TYPE_8__ {int val2; int next; int /*<<< orphan*/  val1; } ;
typedef  TYPE_1__ OpcodeTable ;
typedef  TYPE_2__ GetByteContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 unsigned int AV_RL32 (int /*<<< orphan*/ *) ; 
 unsigned int bytestream2_get_bytes_left (TYPE_2__*) ; 
 int bytestream2_get_le32 (TYPE_2__*) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_2__*,int) ; 
 int fill_optable (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int get_opcodes(GetByteContext *gb, uint32_t *table, uint8_t *dst, int op_size, int nb_elements)
{
    OpcodeTable optable[1024];
    int sum, x, val, lshift, rshift, ret, i, idx;
    int64_t size_in_bits;
    unsigned endoffset, newoffset, offset;
    unsigned next;
    uint8_t *src = (uint8_t *)gb->buffer;

    ret = fill_optable(table, optable, nb_elements);
    if (ret < 0)
        return ret;

    size_in_bits = bytestream2_get_le32(gb);
    endoffset = ((size_in_bits + 7) >> 3) - 4;
    if (endoffset <= 0 || bytestream2_get_bytes_left(gb) < endoffset)
        return AVERROR_INVALIDDATA;

    offset = endoffset;
    next = AV_RL32(src + endoffset);
    rshift = (((size_in_bits & 0xFF) - 1) & 7) + 15;
    lshift = 32 - rshift;
    idx = (next >> rshift) & 0x3FF;
    for (i = 0; i < op_size; i++) {
        dst[i] = optable[idx].val1;
        val = optable[idx].val2;
        sum = val + lshift;
        x = (next << lshift) >> 1 >> (31 - val);
        newoffset = offset - (sum >> 3);
        lshift = sum & 7;
        idx = x + optable[idx].next;
        offset = newoffset;
        if (offset > endoffset)
            return AVERROR_INVALIDDATA;
        next = AV_RL32(src + offset);
    }

    bytestream2_skip(gb, (size_in_bits + 7 >> 3) - 4);

    return 0;
}