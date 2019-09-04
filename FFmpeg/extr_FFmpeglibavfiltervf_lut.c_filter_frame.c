#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_18__ {TYPE_3__** outputs; TYPE_1__* priv; } ;
struct TYPE_17__ {int w; int h; TYPE_4__* dst; } ;
struct TYPE_16__ {int height; int* linesize; size_t** data; } ;
struct TYPE_15__ {size_t** lut; int step; int vsub; int hsub; scalar_t__ is_16bit; int /*<<< orphan*/  is_planar; scalar_t__ is_rgb; } ;
typedef  TYPE_1__ LutContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CEIL_RSHIFT (int,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_frame_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_2__**) ; 
 scalar_t__ av_frame_is_writable (TYPE_2__*) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 TYPE_2__* ff_get_video_buffer (TYPE_3__*,int,int) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    LutContext *s = ctx->priv;
    AVFilterLink *outlink = ctx->outputs[0];
    AVFrame *out;
    int i, j, plane, direct = 0;

    if (av_frame_is_writable(in)) {
        direct = 1;
        out = in;
    } else {
        out = ff_get_video_buffer(outlink, outlink->w, outlink->h);
        if (!out) {
            av_frame_free(&in);
            return AVERROR(ENOMEM);
        }
        av_frame_copy_props(out, in);
    }

    if (s->is_rgb && s->is_16bit && !s->is_planar) {
        /* packed, 16-bit */
        uint16_t *inrow, *outrow, *inrow0, *outrow0;
        const int w = inlink->w;
        const int h = in->height;
        const uint16_t (*tab)[256*256] = (const uint16_t (*)[256*256])s->lut;
        const int in_linesize  =  in->linesize[0] / 2;
        const int out_linesize = out->linesize[0] / 2;
        const int step = s->step;

        inrow0  = (uint16_t*) in ->data[0];
        outrow0 = (uint16_t*) out->data[0];

        for (i = 0; i < h; i ++) {
            inrow  = inrow0;
            outrow = outrow0;
            for (j = 0; j < w; j++) {

                switch (step) {
#if HAVE_BIGENDIAN
                case 4:  outrow[3] = av_bswap16(tab[3][av_bswap16(inrow[3])]); // Fall-through
                case 3:  outrow[2] = av_bswap16(tab[2][av_bswap16(inrow[2])]); // Fall-through
                case 2:  outrow[1] = av_bswap16(tab[1][av_bswap16(inrow[1])]); // Fall-through
                default: outrow[0] = av_bswap16(tab[0][av_bswap16(inrow[0])]);
#else
                case 4:  outrow[3] = tab[3][inrow[3]]; // Fall-through
                case 3:  outrow[2] = tab[2][inrow[2]]; // Fall-through
                case 2:  outrow[1] = tab[1][inrow[1]]; // Fall-through
                default: outrow[0] = tab[0][inrow[0]];
#endif
                }
                outrow += step;
                inrow  += step;
            }
            inrow0  += in_linesize;
            outrow0 += out_linesize;
        }
    } else if (s->is_rgb && !s->is_planar) {
        /* packed */
        uint8_t *inrow, *outrow, *inrow0, *outrow0;
        const int w = inlink->w;
        const int h = in->height;
        const uint16_t (*tab)[256*256] = (const uint16_t (*)[256*256])s->lut;
        const int in_linesize  =  in->linesize[0];
        const int out_linesize = out->linesize[0];
        const int step = s->step;

        inrow0  = in ->data[0];
        outrow0 = out->data[0];

        for (i = 0; i < h; i ++) {
            inrow  = inrow0;
            outrow = outrow0;
            for (j = 0; j < w; j++) {
                switch (step) {
                case 4:  outrow[3] = tab[3][inrow[3]]; // Fall-through
                case 3:  outrow[2] = tab[2][inrow[2]]; // Fall-through
                case 2:  outrow[1] = tab[1][inrow[1]]; // Fall-through
                default: outrow[0] = tab[0][inrow[0]];
                }
                outrow += step;
                inrow  += step;
            }
            inrow0  += in_linesize;
            outrow0 += out_linesize;
        }
    } else if (s->is_16bit) {
        // planar >8 bit depth
        uint16_t *inrow, *outrow;

        for (plane = 0; plane < 4 && in->data[plane] && in->linesize[plane]; plane++) {
            int vsub = plane == 1 || plane == 2 ? s->vsub : 0;
            int hsub = plane == 1 || plane == 2 ? s->hsub : 0;
            int h = AV_CEIL_RSHIFT(inlink->h, vsub);
            int w = AV_CEIL_RSHIFT(inlink->w, hsub);
            const uint16_t *tab = s->lut[plane];
            const int in_linesize  =  in->linesize[plane] / 2;
            const int out_linesize = out->linesize[plane] / 2;

            inrow  = (uint16_t *)in ->data[plane];
            outrow = (uint16_t *)out->data[plane];

            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++) {
#if HAVE_BIGENDIAN
                    outrow[j] = av_bswap16(tab[av_bswap16(inrow[j])]);
#else
                    outrow[j] = tab[inrow[j]];
#endif
                }
                inrow  += in_linesize;
                outrow += out_linesize;
            }
        }
    } else {
        /* planar 8bit depth */
        uint8_t *inrow, *outrow;

        for (plane = 0; plane < 4 && in->data[plane] && in->linesize[plane]; plane++) {
            int vsub = plane == 1 || plane == 2 ? s->vsub : 0;
            int hsub = plane == 1 || plane == 2 ? s->hsub : 0;
            int h = AV_CEIL_RSHIFT(inlink->h, vsub);
            int w = AV_CEIL_RSHIFT(inlink->w, hsub);
            const uint16_t *tab = s->lut[plane];
            const int in_linesize  =  in->linesize[plane];
            const int out_linesize = out->linesize[plane];

            inrow  = in ->data[plane];
            outrow = out->data[plane];

            for (i = 0; i < h; i++) {
                for (j = 0; j < w; j++)
                    outrow[j] = tab[inrow[j]];
                inrow  += in_linesize;
                outrow += out_linesize;
            }
        }
    }

    if (!direct)
        av_frame_free(&in);

    return ff_filter_frame(outlink, out);
}