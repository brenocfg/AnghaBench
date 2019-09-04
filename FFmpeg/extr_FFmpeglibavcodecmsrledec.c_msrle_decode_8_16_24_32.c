#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int height; } ;
struct TYPE_6__ {int* linesize; void*** data; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FFABS (int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_bufferu (int /*<<< orphan*/ *,void**,int) ; 
 void* bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le16u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_le32u (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void**,void*,int) ; 

__attribute__((used)) static int msrle_decode_8_16_24_32(AVCodecContext *avctx, AVFrame *pic,
                                   int depth, GetByteContext *gb)
{
    uint8_t *output, *output_end;
    int p1, p2, line=avctx->height - 1, pos=0, i;
    uint16_t pix16;
    uint32_t pix32;
    unsigned int width= FFABS(pic->linesize[0]) / (depth >> 3);

    output     = pic->data[0] + (avctx->height - 1) * pic->linesize[0];
    output_end = output + FFABS(pic->linesize[0]);

    while (bytestream2_get_bytes_left(gb) > 0) {
        p1 = bytestream2_get_byteu(gb);
        if(p1 == 0) { //Escape code
            p2 = bytestream2_get_byte(gb);
            if(p2 == 0) { //End-of-line
                if (--line < 0) {
                    if (bytestream2_get_be16(gb) == 1) { // end-of-picture
                        return 0;
                    } else {
                        av_log(avctx, AV_LOG_ERROR,
                               "Next line is beyond picture bounds (%d bytes left)\n",
                               bytestream2_get_bytes_left(gb));
                        return AVERROR_INVALIDDATA;
                    }
                }
                output = pic->data[0] + line * pic->linesize[0];
                output_end = output + FFABS(pic->linesize[0]);
                pos = 0;
                continue;
            } else if(p2 == 1) { //End-of-picture
                return 0;
            } else if(p2 == 2) { //Skip
                p1 = bytestream2_get_byte(gb);
                p2 = bytestream2_get_byte(gb);
                line -= p2;
                pos += p1;
                if (line < 0 || pos >= width){
                    av_log(avctx, AV_LOG_ERROR, "Skip beyond picture bounds\n");
                    return -1;
                }
                output = pic->data[0] + line * pic->linesize[0] + pos * (depth >> 3);
                output_end = pic->data[0] + line * pic->linesize[0] + FFABS(pic->linesize[0]);
                continue;
            }
            // Copy data
            if (output + p2 * (depth >> 3) > output_end) {
                bytestream2_skip(gb, 2 * (depth >> 3));
                continue;
            } else if (bytestream2_get_bytes_left(gb) < p2 * (depth >> 3)) {
                av_log(avctx, AV_LOG_ERROR, "bytestream overrun\n");
                return AVERROR_INVALIDDATA;
            }

            if ((depth == 8) || (depth == 24)) {
                bytestream2_get_bufferu(gb, output, p2 * (depth >> 3));
                output += p2 * (depth >> 3);

                // RLE8 copy is actually padded - and runs are not!
                if(depth == 8 && (p2 & 1)) {
                    bytestream2_skip(gb, 1);
                }
            } else if (depth == 16) {
                for(i = 0; i < p2; i++) {
                    *(uint16_t*)output = bytestream2_get_le16u(gb);
                    output += 2;
                }
            } else if (depth == 32) {
                for(i = 0; i < p2; i++) {
                    *(uint32_t*)output = bytestream2_get_le32u(gb);
                    output += 4;
                }
            }
            pos += p2;
        } else { //run of pixels
            uint8_t pix[3]; //original pixel
            if (output + p1 * (depth >> 3) > output_end)
                continue;

            switch(depth){
            case  8:
                pix[0] = bytestream2_get_byte(gb);
                memset(output, pix[0], p1);
                output += p1;
                break;
            case 16:
                pix16  = bytestream2_get_le16(gb);
                for(i = 0; i < p1; i++) {
                        *(uint16_t*)output = pix16;
                        output += 2;
                }
                break;
            case 24:
                pix[0] = bytestream2_get_byte(gb);
                pix[1] = bytestream2_get_byte(gb);
                pix[2] = bytestream2_get_byte(gb);
                for(i = 0; i < p1; i++) {
                        *output++ = pix[0];
                        *output++ = pix[1];
                        *output++ = pix[2];
                }
                break;
            case 32:
                pix32  = bytestream2_get_le32(gb);
                for(i = 0; i < p1; i++) {
                        *(uint32_t*)output = pix32;
                        output += 4;
                }
                break;
            }
            pos += p1;
        }
    }

    av_log(avctx, AV_LOG_WARNING, "MS RLE warning: no end-of-picture code\n");
    return 0;
}