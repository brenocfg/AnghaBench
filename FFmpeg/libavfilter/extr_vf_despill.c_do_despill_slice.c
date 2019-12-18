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
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int height; float** data; int* linesize; int width; } ;
struct TYPE_5__ {int* co; float brightness; float redscale; float greenscale; float bluescale; float spillmix; float spillexpand; scalar_t__ alpha; scalar_t__ type; } ;
typedef  TYPE_1__ DespillContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 float FFMAX (float,float) ; 
 float av_clip_uint8 (float) ; 

__attribute__((used)) static int do_despill_slice(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    DespillContext *s = ctx->priv;
    AVFrame *frame = arg;
    const int ro = s->co[0], go = s->co[1], bo = s->co[2], ao = s->co[3];
    const int slice_start = (frame->height * jobnr) / nb_jobs;
    const int slice_end = (frame->height * (jobnr + 1)) / nb_jobs;
    const float brightness = s->brightness;
    const float redscale = s->redscale;
    const float greenscale = s->greenscale;
    const float bluescale = s->bluescale;
    const float spillmix = s->spillmix;
    const float factor = (1.f - spillmix) * (1.f - s->spillexpand);
    float red, green, blue;
    int x, y;

    for (y = slice_start; y < slice_end; y++) {
        uint8_t *dst = frame->data[0] + y * frame->linesize[0];

        for (x = 0; x < frame->width; x++) {
            float spillmap;

            red   = dst[x * 4 + ro] / 255.f;
            green = dst[x * 4 + go] / 255.f;
            blue  = dst[x * 4 + bo] / 255.f;

            if (s->type) {
                spillmap = FFMAX(blue  - (red * spillmix + green * factor), 0.f);
            } else {
                spillmap = FFMAX(green - (red * spillmix + blue  * factor), 0.f);
            }

            red   = FFMAX(red   + spillmap * redscale   + brightness * spillmap, 0.f);
            green = FFMAX(green + spillmap * greenscale + brightness * spillmap, 0.f);
            blue  = FFMAX(blue  + spillmap * bluescale  + brightness * spillmap, 0.f);

            dst[x * 4 + ro] = av_clip_uint8(red   * 255);
            dst[x * 4 + go] = av_clip_uint8(green * 255);
            dst[x * 4 + bo] = av_clip_uint8(blue  * 255);
            if (s->alpha) {
                spillmap = 1.f - spillmap;
                dst[x * 4 + ao] = av_clip_uint8(spillmap * 255);
            }
        }
    }

    return 0;
}