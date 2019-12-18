#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int64_t ;
struct TYPE_11__ {scalar_t__* pixels; int /*<<< orphan*/  pixels_size; scalar_t__* buf; int /*<<< orphan*/  buf_size; } ;
typedef  TYPE_1__ XPMDecContext ;
struct TYPE_14__ {int height; int width; int /*<<< orphan*/  pix_fmt; TYPE_1__* priv_data; } ;
struct TYPE_13__ {int* linesize; int key_frame; int /*<<< orphan*/  pict_type; scalar_t__* data; } ;
struct TYPE_12__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PIX_FMT_BGRA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int NB_ELEMENTS ; 
 int ascii2index (scalar_t__ const*,int) ; 
 int /*<<< orphan*/  av_fast_padded_malloc (scalar_t__**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ color_string_to_rgba (scalar_t__ const*,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_4__*,int,int) ; 
 scalar_t__ memcmp (scalar_t__ const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mod_strcspn (scalar_t__ const*,char*) ; 
 int sscanf (scalar_t__ const*,char*,int*,int*,int*,int*) ; 
 int strcspn (scalar_t__ const*,char*) ; 
 scalar_t__* strstr (scalar_t__ const*,char*) ; 

__attribute__((used)) static int xpm_decode_frame(AVCodecContext *avctx, void *data,
                            int *got_frame, AVPacket *avpkt)
{
    XPMDecContext *x = avctx->priv_data;
    AVFrame *p=data;
    const uint8_t *end, *ptr;
    int ncolors, cpp, ret, i, j;
    int64_t size;
    uint32_t *dst;
    int width, height;

    avctx->pix_fmt = AV_PIX_FMT_BGRA;

    av_fast_padded_malloc(&x->buf, &x->buf_size, avpkt->size);
    if (!x->buf)
        return AVERROR(ENOMEM);
    memcpy(x->buf, avpkt->data, avpkt->size);
    x->buf[avpkt->size] = 0;

    ptr = x->buf;
    end = x->buf + avpkt->size;
    while (end - ptr > 9 && memcmp(ptr, "/* XPM */", 9))
        ptr++;

    if (end - ptr <= 9) {
        av_log(avctx, AV_LOG_ERROR, "missing signature\n");
        return AVERROR_INVALIDDATA;
    }

    ptr += mod_strcspn(ptr, "\"");
    if (sscanf(ptr, "\"%u %u %u %u\",",
               &width, &height, &ncolors, &cpp) != 4) {
        av_log(avctx, AV_LOG_ERROR, "missing image parameters\n");
        return AVERROR_INVALIDDATA;
    }

    if ((ret = ff_set_dimensions(avctx, width, height)) < 0)
        return ret;

    if ((ret = ff_get_buffer(avctx, p, 0)) < 0)
        return ret;

    if (cpp <= 0 || cpp >= 5) {
        av_log(avctx, AV_LOG_ERROR, "unsupported/invalid number of chars per pixel: %d\n", cpp);
        return AVERROR_INVALIDDATA;
    }

    size = 1;
    for (i = 0; i < cpp; i++)
        size *= NB_ELEMENTS;

    if (ncolors <= 0 || ncolors > size) {
        av_log(avctx, AV_LOG_ERROR, "invalid number of colors: %d\n", ncolors);
        return AVERROR_INVALIDDATA;
    }

    size *= 4;

    av_fast_padded_malloc(&x->pixels, &x->pixels_size, size);
    if (!x->pixels)
        return AVERROR(ENOMEM);

    ptr += mod_strcspn(ptr, ",") + 1;
    if (end - ptr < 1)
        return AVERROR_INVALIDDATA;

    for (i = 0; i < ncolors; i++) {
        const uint8_t *index;
        int len;

        ptr += mod_strcspn(ptr, "\"") + 1;
        if (end - ptr < cpp)
            return AVERROR_INVALIDDATA;
        index = ptr;
        ptr += cpp;

        ptr = strstr(ptr, "c ");
        if (ptr) {
            ptr += 2;
        } else {
            return AVERROR_INVALIDDATA;
        }

        len = strcspn(ptr, "\" ");

        if ((ret = ascii2index(index, cpp)) < 0)
            return ret;

        x->pixels[ret] = color_string_to_rgba(ptr, len);
        ptr += mod_strcspn(ptr, ",") + 1;
        if (end - ptr < 1)
            return AVERROR_INVALIDDATA;
    }

    for (i = 0; i < avctx->height; i++) {
        dst = (uint32_t *)(p->data[0] + i * p->linesize[0]);
        if (end - ptr < 1)
            return AVERROR_INVALIDDATA;
        ptr += mod_strcspn(ptr, "\"") + 1;
        if (end - ptr < 1)
            return AVERROR_INVALIDDATA;

        for (j = 0; j < avctx->width; j++) {
            if (end - ptr < cpp)
                return AVERROR_INVALIDDATA;

            if ((ret = ascii2index(ptr, cpp)) < 0)
                return ret;

            *dst++ = x->pixels[ret];
            ptr += cpp;
        }
        ptr += mod_strcspn(ptr, ",") + 1;
    }

    p->key_frame = 1;
    p->pict_type = AV_PICTURE_TYPE_I;

    *got_frame = 1;

    return avpkt->size;
}