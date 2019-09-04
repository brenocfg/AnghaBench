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
struct TYPE_8__ {int width; int height; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int width; int height; int quality; int /*<<< orphan*/  cq; int /*<<< orphan*/  lq; int /*<<< orphan*/  rtj; int /*<<< orphan*/  pic; int /*<<< orphan*/  decomp_buf; int /*<<< orphan*/  decomp_size; } ;
typedef  TYPE_1__ NuvContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LZO_OUTPUT_PADDING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 int RTJPEG_HEADER_SIZE ; 
 int /*<<< orphan*/  av_fast_malloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int av_image_check_size (int,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_rtjpeg_decode_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_quant_quality (TYPE_1__*,int) ; 

__attribute__((used)) static int codec_reinit(AVCodecContext *avctx, int width, int height,
                        int quality)
{
    NuvContext *c = avctx->priv_data;
    int ret;

    width  = FFALIGN(width,  2);
    height = FFALIGN(height, 2);
    if (quality >= 0)
        get_quant_quality(c, quality);
    if (width != c->width || height != c->height) {
        // also reserve space for a possible additional header
        int buf_size = height * width * 3 / 2
                     + FFMAX(AV_LZO_OUTPUT_PADDING, AV_INPUT_BUFFER_PADDING_SIZE)
                     + RTJPEG_HEADER_SIZE;
        if (buf_size > INT_MAX/8)
            return -1;
        if ((ret = av_image_check_size(height, width, 0, avctx)) < 0)
            return ret;
        avctx->width  = c->width  = width;
        avctx->height = c->height = height;
        av_fast_malloc(&c->decomp_buf, &c->decomp_size,
                       buf_size);
        if (!c->decomp_buf) {
            av_log(avctx, AV_LOG_ERROR,
                   "Can't allocate decompression buffer.\n");
            return AVERROR(ENOMEM);
        }
        ff_rtjpeg_decode_init(&c->rtj, c->width, c->height, c->lq, c->cq);
        av_frame_unref(c->pic);
        return 1;
    } else if (quality != c->quality)
        ff_rtjpeg_decode_init(&c->rtj, c->width, c->height, c->lq, c->cq);

    return 0;
}