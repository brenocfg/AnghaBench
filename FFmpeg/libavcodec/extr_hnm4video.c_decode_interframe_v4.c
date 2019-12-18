#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int width; int height; int* current; int* previous; } ;
typedef  TYPE_1__ Hnm4VideoContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int*,int) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_interframe_v4(AVCodecContext *avctx, uint8_t *src, uint32_t size)
{
    Hnm4VideoContext *hnm = avctx->priv_data;
    GetByteContext gb;
    uint32_t writeoffset = 0;
    int count, left, offset;
    uint8_t tag, previous, backline, backward, swap;

    bytestream2_init(&gb, src, size);

    while (bytestream2_tell(&gb) < size) {
        count = bytestream2_peek_byte(&gb) & 0x1F;
        if (count == 0) {
            tag = bytestream2_get_byte(&gb) & 0xE0;
            tag = tag >> 5;

            if (tag == 0) {
                if (writeoffset + 2 > hnm->width * hnm->height) {
                    av_log(avctx, AV_LOG_ERROR, "writeoffset out of bounds\n");
                    return AVERROR_INVALIDDATA;
                }
                hnm->current[writeoffset++] = bytestream2_get_byte(&gb);
                hnm->current[writeoffset++] = bytestream2_get_byte(&gb);
            } else if (tag == 1) {
                writeoffset += bytestream2_get_byte(&gb) * 2;
            } else if (tag == 2) {
                count = bytestream2_get_le16(&gb);
                count *= 2;
                writeoffset += count;
            } else if (tag == 3) {
                count = bytestream2_get_byte(&gb) * 2;
                if (writeoffset + count > hnm->width * hnm->height) {
                    av_log(avctx, AV_LOG_ERROR, "writeoffset out of bounds\n");
                    return AVERROR_INVALIDDATA;
                }
                while (count > 0) {
                    hnm->current[writeoffset++] = bytestream2_peek_byte(&gb);
                    count--;
                }
                bytestream2_skip(&gb, 1);
            } else {
                break;
            }
            if (writeoffset > hnm->width * hnm->height) {
                av_log(avctx, AV_LOG_ERROR, "writeoffset out of bounds\n");
                return AVERROR_INVALIDDATA;
            }
        } else {
            previous = bytestream2_peek_byte(&gb) & 0x20;
            backline = bytestream2_peek_byte(&gb) & 0x40;
            backward = bytestream2_peek_byte(&gb) & 0x80;
            bytestream2_skip(&gb, 1);
            swap   = bytestream2_peek_byte(&gb) & 0x01;
            offset = bytestream2_get_le16(&gb);
            offset = (offset >> 1) & 0x7FFF;
            offset = writeoffset + (offset * 2) - 0x8000;

            left = count;

            if (!backward && offset + 2*count > hnm->width * hnm->height) {
                av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds\n");
                return AVERROR_INVALIDDATA;
            } else if (backward && offset + 1 >= hnm->width * hnm->height) {
                av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds\n");
                return AVERROR_INVALIDDATA;
            } else if (writeoffset + 2*count > hnm->width * hnm->height) {
                av_log(avctx, AV_LOG_ERROR,
                       "Attempting to write out of bounds\n");
                return AVERROR_INVALIDDATA;

            }
            if(backward) {
                if (offset < (!!backline)*(2 * hnm->width - 1) + 2*(left-1)) {
                    av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds\n");
                    return AVERROR_INVALIDDATA;
                }
            } else {
                if (offset < (!!backline)*(2 * hnm->width - 1)) {
                    av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds\n");
                    return AVERROR_INVALIDDATA;
                }
            }

            if (previous) {
                while (left > 0) {
                    if (backline) {
                        hnm->current[writeoffset++] = hnm->previous[offset - (2 * hnm->width) + 1];
                        hnm->current[writeoffset++] = hnm->previous[offset++];
                        offset++;
                    } else {
                        hnm->current[writeoffset++] = hnm->previous[offset++];
                        hnm->current[writeoffset++] = hnm->previous[offset++];
                    }
                    if (backward)
                        offset -= 4;
                    left--;
                }
            } else {
                while (left > 0) {
                    if (backline) {
                        hnm->current[writeoffset++] = hnm->current[offset - (2 * hnm->width) + 1];
                        hnm->current[writeoffset++] = hnm->current[offset++];
                        offset++;
                    } else {
                        hnm->current[writeoffset++] = hnm->current[offset++];
                        hnm->current[writeoffset++] = hnm->current[offset++];
                    }
                    if (backward)
                        offset -= 4;
                    left--;
                }
            }

            if (swap) {
                left         = count;
                writeoffset -= count * 2;
                while (left > 0) {
                    swap = hnm->current[writeoffset];
                    hnm->current[writeoffset] = hnm->current[writeoffset + 1];
                    hnm->current[writeoffset + 1] = swap;
                    left--;
                    writeoffset += 2;
                }
            }
        }
    }
    return 0;
}