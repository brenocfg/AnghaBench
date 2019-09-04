#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  float uint8_t ;
struct TYPE_5__ {float* lcoeffs; float intensity; float const* balance; } ;
typedef  TYPE_1__ VibranceContext ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int width; int height; int* linesize; float** data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 float FFMAX3 (float,float,float) ; 
 float FFMIN3 (float,float,float) ; 
 float FFSIGN (float const) ; 
 float av_clip_uint8 (float) ; 
 float lerpf (float,float,float const) ; 

__attribute__((used)) static int vibrance_slice8(AVFilterContext *avctx, void *arg, int jobnr, int nb_jobs)
{
    VibranceContext *s = avctx->priv;
    AVFrame *frame = arg;
    const int width = frame->width;
    const int height = frame->height;
    const float gc = s->lcoeffs[0];
    const float bc = s->lcoeffs[1];
    const float rc = s->lcoeffs[2];
    const float intensity = s->intensity;
    const float gintensity = intensity * s->balance[0];
    const float bintensity = intensity * s->balance[1];
    const float rintensity = intensity * s->balance[2];
    const int slice_start = (height * jobnr) / nb_jobs;
    const int slice_end = (height * (jobnr + 1)) / nb_jobs;
    const int glinesize = frame->linesize[0];
    const int blinesize = frame->linesize[1];
    const int rlinesize = frame->linesize[2];
    uint8_t *gptr = frame->data[0] + slice_start * glinesize;
    uint8_t *bptr = frame->data[1] + slice_start * blinesize;
    uint8_t *rptr = frame->data[2] + slice_start * rlinesize;

    for (int y = slice_start; y < slice_end; y++) {
        for (int x = 0; x < width; x++) {
            float g = gptr[x] / 255.f;
            float b = bptr[x] / 255.f;
            float r = rptr[x] / 255.f;
            float max_color = FFMAX3(r, g, b);
            float min_color = FFMIN3(r, g, b);
            float color_saturation = max_color - min_color;
            float luma = g * gc + r * rc + b * bc;
            const float cg = 1.f + gintensity * (1.f - FFSIGN(gintensity) * color_saturation);
            const float cb = 1.f + bintensity * (1.f - FFSIGN(bintensity) * color_saturation);
            const float cr = 1.f + rintensity * (1.f - FFSIGN(rintensity) * color_saturation);

            g = lerpf(luma, g, cg);
            b = lerpf(luma, b, cb);
            r = lerpf(luma, r, cr);

            gptr[x] = av_clip_uint8(g * 255.f);
            bptr[x] = av_clip_uint8(b * 255.f);
            rptr[x] = av_clip_uint8(r * 255.f);
        }

        gptr += glinesize;
        bptr += blinesize;
        rptr += rlinesize;
    }

    return 0;
}