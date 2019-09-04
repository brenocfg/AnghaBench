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
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {int** data; int /*<<< orphan*/ * linesize; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_rle_bpp4(AVCodecContext *avctx, AVFrame *p, GetByteContext *gbc)
{
    int offset = avctx->width;
    uint8_t *outdata = p->data[0];
    int i, j;

    for (i = 0; i < avctx->height; i++) {
        int size, left, code, pix;
        uint8_t *out = outdata;
        int pos = 0;

        /* size of packed line */
        size = left = bytestream2_get_be16(gbc);
        if (bytestream2_get_bytes_left(gbc) < size)
            return AVERROR_INVALIDDATA;

        /* decode line */
        while (left > 0) {
            code = bytestream2_get_byte(gbc);
            if (code & 0x80 ) { /* run */
                pix = bytestream2_get_byte(gbc);
                for (j = 0; j < 257 - code; j++) {
                    if (pos < offset)
                        out[pos++] = (pix & 0xF0) >> 4;
                    if (pos < offset)
                        out[pos++] = pix & 0xF;
                }
                left  -= 2;
            } else { /* copy */
                for (j = 0; j < code + 1; j++) {
                    pix = bytestream2_get_byte(gbc);
                    if (pos < offset)
                        out[pos++] = (pix & 0xF0) >> 4;
                    if (pos < offset)
                        out[pos++] = pix & 0xF;
                }
                left  -= 1 + (code + 1);
            }
        }
        outdata += p->linesize[0];
    }
    return 0;
}