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
typedef  size_t uint32_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {size_t width; size_t height; size_t* current; size_t* previous; } ;
typedef  TYPE_1__ Hnm4VideoContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 size_t bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int*,size_t) ; 
 int bytestream2_peek_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 size_t bytestream2_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decode_interframe_v4a(AVCodecContext *avctx, uint8_t *src,
                                  uint32_t size)
{
    Hnm4VideoContext *hnm = avctx->priv_data;
    GetByteContext gb;
    uint32_t writeoffset = 0, offset;
    uint8_t tag, count, previous, delta;

    bytestream2_init(&gb, src, size);

    while (bytestream2_tell(&gb) < size) {
        count = bytestream2_peek_byte(&gb) & 0x3F;
        if (count == 0) {
            tag = bytestream2_get_byte(&gb) & 0xC0;
            tag = tag >> 6;
            if (tag == 0) {
                writeoffset += bytestream2_get_byte(&gb);
            } else if (tag == 1) {
                if (writeoffset + hnm->width >= hnm->width * hnm->height) {
                    av_log(avctx, AV_LOG_ERROR, "writeoffset out of bounds\n");
                    break;
                }
                hnm->current[writeoffset]              = bytestream2_get_byte(&gb);
                hnm->current[writeoffset + hnm->width] = bytestream2_get_byte(&gb);
                writeoffset++;
            } else if (tag == 2) {
                writeoffset += hnm->width;
            } else if (tag == 3) {
                break;
            }
            if (writeoffset > hnm->width * hnm->height) {
                av_log(avctx, AV_LOG_ERROR, "writeoffset out of bounds\n");
                break;
            }
        } else {
            delta    = bytestream2_peek_byte(&gb) & 0x80;
            previous = bytestream2_peek_byte(&gb) & 0x40;
            bytestream2_skip(&gb, 1);

            offset  = writeoffset;
            offset += bytestream2_get_le16(&gb);

            if (delta) {
                if (offset < 0x10000) {
                    av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds\n");
                    break;
                }
                offset -= 0x10000;
            }

            if (offset + hnm->width + count >= hnm->width * hnm->height) {
                av_log(avctx, AV_LOG_ERROR, "Attempting to read out of bounds\n");
                break;
            } else if (writeoffset + hnm->width + count >= hnm->width * hnm->height) {
                av_log(avctx, AV_LOG_ERROR, "Attempting to write out of bounds\n");
                break;
            }

            if (previous) {
                while (count > 0) {
                    hnm->current[writeoffset]              = hnm->previous[offset];
                    hnm->current[writeoffset + hnm->width] = hnm->previous[offset + hnm->width];
                    writeoffset++;
                    offset++;
                    count--;
                }
            } else {
                while (count > 0) {
                    hnm->current[writeoffset]              = hnm->current[offset];
                    hnm->current[writeoffset + hnm->width] = hnm->current[offset + hnm->width];
                    writeoffset++;
                    offset++;
                    count--;
                }
            }
        }
    }
}