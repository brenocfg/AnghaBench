#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_16__ {int* mc_charmap; int* mc_colram; int* mc_charset; int* mc_meta_charset; int* mc_best_cb; int mc_use_5col; int mc_lifetime; int mc_frame_counter; scalar_t__ next_pts; int /*<<< orphan*/  randctx; } ;
struct TYPE_15__ {scalar_t__ extradata; int /*<<< orphan*/  width; int /*<<< orphan*/  height; TYPE_4__* priv_data; } ;
struct TYPE_14__ {scalar_t__ pts; } ;
struct TYPE_13__ {int* data; scalar_t__ pts; scalar_t__ dts; int size; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_4__ A64Context ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_WB32 (scalar_t__,int) ; 
 int C64XRES ; 
 int C64YRES ; 
 int /*<<< orphan*/  CHARSET_CHARS ; 
 scalar_t__ CROP_SCREENS ; 
 int FFMIN (int /*<<< orphan*/ ,int) ; 
 int INTERLACED ; 
 int /*<<< orphan*/  a64_compress_colram (int*,int*,int*) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int avpriv_do_elbg (int*,int,int,int*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int avpriv_init_elbg (int*,int,int,int*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int ff_alloc_packet2 (TYPE_3__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  render_charset (TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  to_meta_with_crop (TYPE_3__*,TYPE_2__ const*,int*) ; 

__attribute__((used)) static int a64multi_encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                                 const AVFrame *p, int *got_packet)
{
    A64Context *c = avctx->priv_data;

    int frame;
    int x, y;
    int b_height;
    int b_width;

    int req_size, ret;
    uint8_t *buf = NULL;

    int *charmap     = c->mc_charmap;
    uint8_t *colram  = c->mc_colram;
    uint8_t *charset = c->mc_charset;
    int *meta        = c->mc_meta_charset;
    int *best_cb     = c->mc_best_cb;

    int charset_size = 0x800 * (INTERLACED + 1);
    int colram_size  = 0x100 * c->mc_use_5col;
    int screen_size;

    if(CROP_SCREENS) {
        b_height = FFMIN(avctx->height,C64YRES) >> 3;
        b_width  = FFMIN(avctx->width ,C64XRES) >> 3;
        screen_size = b_width * b_height;
    } else {
        b_height = C64YRES >> 3;
        b_width  = C64XRES >> 3;
        screen_size = 0x400;
    }

    /* no data, means end encoding asap */
    if (!p) {
        /* all done, end encoding */
        if (!c->mc_lifetime) return 0;
        /* no more frames in queue, prepare to flush remaining frames */
        if (!c->mc_frame_counter) {
            c->mc_lifetime = 0;
        }
        /* still frames in queue so limit lifetime to remaining frames */
        else c->mc_lifetime = c->mc_frame_counter;
    /* still new data available */
    } else {
        /* fill up mc_meta_charset with data until lifetime exceeds */
        if (c->mc_frame_counter < c->mc_lifetime) {
            to_meta_with_crop(avctx, p, meta + 32000 * c->mc_frame_counter);
            c->mc_frame_counter++;
            if (c->next_pts == AV_NOPTS_VALUE)
                c->next_pts = p->pts;
            /* lifetime is not reached so wait for next frame first */
            return 0;
        }
    }

    /* lifetime reached so now convert X frames at once */
    if (c->mc_frame_counter == c->mc_lifetime) {
        req_size = 0;
        /* any frames to encode? */
        if (c->mc_lifetime) {
            int alloc_size = charset_size + c->mc_lifetime*(screen_size + colram_size);
            if ((ret = ff_alloc_packet2(avctx, pkt, alloc_size, 0)) < 0)
                return ret;
            buf = pkt->data;

            /* calc optimal new charset + charmaps */
            ret = avpriv_init_elbg(meta, 32, 1000 * c->mc_lifetime, best_cb,
                               CHARSET_CHARS, 50, charmap, &c->randctx);
            if (ret < 0)
                return ret;
            ret = avpriv_do_elbg(meta, 32, 1000 * c->mc_lifetime, best_cb,
                             CHARSET_CHARS, 50, charmap, &c->randctx);
            if (ret < 0)
                return ret;

            /* create colorram map and a c64 readable charset */
            render_charset(avctx, charset, colram);

            /* copy charset to buf */
            memcpy(buf, charset, charset_size);

            /* advance pointers */
            buf      += charset_size;
            req_size += charset_size;
        }

        /* write x frames to buf */
        for (frame = 0; frame < c->mc_lifetime; frame++) {
            /* copy charmap to buf. buf is uchar*, charmap is int*, so no memcpy here, sorry */
            for (y = 0; y < b_height; y++) {
                for (x = 0; x < b_width; x++) {
                    buf[y * b_width + x] = charmap[y * b_width + x];
                }
            }
            /* advance pointers */
            buf += screen_size;
            req_size += screen_size;

            /* compress and copy colram to buf */
            if (c->mc_use_5col) {
                a64_compress_colram(buf, charmap, colram);
                /* advance pointers */
                buf += colram_size;
                req_size += colram_size;
            }

            /* advance to next charmap */
            charmap += 1000;
        }

        AV_WB32(avctx->extradata + 4,  c->mc_frame_counter);
        AV_WB32(avctx->extradata + 8,  charset_size);
        AV_WB32(avctx->extradata + 12, screen_size + colram_size);

        /* reset counter */
        c->mc_frame_counter = 0;

        pkt->pts = pkt->dts = c->next_pts;
        c->next_pts         = AV_NOPTS_VALUE;

        av_assert0(pkt->size >= req_size);
        pkt->size   = req_size;
        pkt->flags |= AV_PKT_FLAG_KEY;
        *got_packet = !!req_size;
    }
    return 0;
}