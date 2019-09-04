#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  void* uint16_t ;
struct TYPE_11__ {int width; scalar_t__ codec_id; int codec_tag; int extradata_size; int height; int /*<<< orphan*/ * extradata; } ;
struct TYPE_10__ {int key_frame; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_9__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_AVRP ; 
 scalar_t__ AV_CODEC_ID_R10K ; 
 scalar_t__ AV_CODEC_ID_R210 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int FFALIGN (int,int) ; 
 int MKTAG (char,char,int /*<<< orphan*/ ,char) ; 
 int av_be2ne32 (int /*<<< orphan*/ ) ; 
 int av_le2ne32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                        AVPacket *avpkt)
{
    int h, w, ret;
    AVFrame *pic = data;
    const uint32_t *src = (const uint32_t *)avpkt->data;
    int aligned_width = FFALIGN(avctx->width,
                                avctx->codec_id == AV_CODEC_ID_R10K ? 1 : 64);
    uint8_t *g_line, *b_line, *r_line;
    int r10 = (avctx->codec_tag & 0xFFFFFF) == MKTAG('r', '1', '0', 0);
    int le = avctx->codec_tag == MKTAG('R', '1', '0', 'k') &&
             avctx->extradata_size >= 12 && !memcmp(&avctx->extradata[4], "DpxE", 4) &&
             !avctx->extradata[11];

    if (avpkt->size < 4 * aligned_width * avctx->height) {
        av_log(avctx, AV_LOG_ERROR, "packet too small\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_get_buffer(avctx, pic, 0)) < 0)
        return ret;

    pic->pict_type = AV_PICTURE_TYPE_I;
    pic->key_frame = 1;
    g_line = pic->data[0];
    b_line = pic->data[1];
    r_line = pic->data[2];

    for (h = 0; h < avctx->height; h++) {
        uint16_t *dstg = (uint16_t *)g_line;
        uint16_t *dstb = (uint16_t *)b_line;
        uint16_t *dstr = (uint16_t *)r_line;
        for (w = 0; w < avctx->width; w++) {
            uint32_t pixel;
            uint16_t r, g, b;
            if (avctx->codec_id == AV_CODEC_ID_AVRP || r10 || le) {
                pixel = av_le2ne32(*src++);
            } else {
                pixel = av_be2ne32(*src++);
            }
            if (avctx->codec_id == AV_CODEC_ID_R210) {
                b =  pixel & 0x3ff;
                g = (pixel >> 10) & 0x3ff;
                r = (pixel >> 20) & 0x3ff;
            } else if (r10) {
                r =  pixel & 0x3ff;
                g = (pixel >> 10) & 0x3ff;
                b = (pixel >> 20) & 0x3ff;
            } else {
                b = (pixel >>  2) & 0x3ff;
                g = (pixel >> 12) & 0x3ff;
                r = (pixel >> 22) & 0x3ff;
            }
            *dstr++ = r;
            *dstg++ = g;
            *dstb++ = b;
        }
        src += aligned_width - avctx->width;
        g_line += pic->linesize[0];
        b_line += pic->linesize[1];
        r_line += pic->linesize[2];
    }

    *got_frame      = 1;

    return avpkt->size;
}