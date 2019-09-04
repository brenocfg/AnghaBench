#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {TYPE_1__* frame; } ;
struct TYPE_7__ {unsigned char** data; int palette_has_changed; int* linesize; } ;
typedef  TYPE_2__ SeqVideoContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB24 (unsigned char*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 unsigned char* seq_decode_op1 (TYPE_2__*,unsigned char const*,unsigned char const*,unsigned char*) ; 
 unsigned char* seq_decode_op2 (TYPE_2__*,unsigned char const*,unsigned char const*,unsigned char*) ; 
 unsigned char* seq_decode_op3 (TYPE_2__*,unsigned char const*,unsigned char const*,unsigned char*) ; 

__attribute__((used)) static int seqvideo_decode(SeqVideoContext *seq, const unsigned char *data, int data_size)
{
    const unsigned char *data_end = data + data_size;
    GetBitContext gb;
    int flags, i, j, x, y, op;
    unsigned char c[3];
    unsigned char *dst;
    uint32_t *palette;

    flags = *data++;

    if (flags & 1) {
        palette = (uint32_t *)seq->frame->data[1];
        if (data_end - data < 256 * 3)
            return AVERROR_INVALIDDATA;
        for (i = 0; i < 256; i++) {
            for (j = 0; j < 3; j++, data++)
                c[j] = (*data << 2) | (*data >> 4);
            palette[i] = 0xFFU << 24 | AV_RB24(c);
        }
        seq->frame->palette_has_changed = 1;
    }

    if (flags & 2) {
        if (data_end - data < 128)
            return AVERROR_INVALIDDATA;
        init_get_bits(&gb, data, 128 * 8); data += 128;
        for (y = 0; y < 128; y += 8)
            for (x = 0; x < 256; x += 8) {
                dst = &seq->frame->data[0][y * seq->frame->linesize[0] + x];
                op = get_bits(&gb, 2);
                switch (op) {
                case 1:
                    data = seq_decode_op1(seq, data, data_end, dst);
                    break;
                case 2:
                    data = seq_decode_op2(seq, data, data_end, dst);
                    break;
                case 3:
                    data = seq_decode_op3(seq, data, data_end, dst);
                    break;
                }
                if (!data)
                    return AVERROR_INVALIDDATA;
            }
    }
    return 0;
}