#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  metabuf ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_12__ {TYPE_1__* priv; TYPE_3__** outputs; } ;
struct TYPE_11__ {TYPE_4__* dst; } ;
struct TYPE_10__ {size_t** data; int* linesize; int /*<<< orphan*/  metadata; } ;
struct TYPE_9__ {int nb_planes; int* rgba_map; float* planewidth; float* planeheight; float* histogram; int depth; scalar_t__ mode; int* planenames; scalar_t__ is_rgb; } ;
typedef  TYPE_1__ EntropyContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterLink ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 float FFABS (scalar_t__) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (TYPE_3__*,TYPE_2__*) ; 
 float log2 (int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVFilterLink *outlink = ctx->outputs[0];
    EntropyContext *s = ctx->priv;
    int plane, y, x;

    for (plane = 0; plane < s->nb_planes; plane++) {
        int cidx = s->is_rgb ? s->rgba_map[plane] : plane;
        const uint8_t *src8 = in->data[plane];
        const uint16_t *src16 = (const uint16_t *)in->data[plane];
        float total = s->planewidth[plane] * s->planeheight[plane];
        float entropy = 0;
        char metabuf[128];
        char key[128];

        memset(s->histogram, 0, (1 << s->depth) * sizeof(*s->histogram));

        if (s->depth <= 8) {
            for (y = 0; y < s->planeheight[plane]; y++) {
                for (x = 0; x < s->planewidth[plane]; x++) {
                    s->histogram[src8[x]]++;
                }

                src8 += in->linesize[plane];
            }
        } else {
            for (y = 0; y < s->planeheight[plane]; y++) {
                for (x = 0; x < s->planewidth[plane]; x++) {
                    s->histogram[src16[x]]++;
                }

                src16 += in->linesize[plane] / 2;
            }
        }

        for (y = 0; y < 1 << s->depth; y++) {
            if (s->mode == 0) {
                if (s->histogram[y]) {
                    float p = s->histogram[y] / total;
                    entropy += -log2(p) * p;
                }
            } else if (s->mode == 1) {
                if (y && (s->histogram[y] - s->histogram[y - 1]) != 0) {
                    float p = FFABS(s->histogram[y] - s->histogram[y - 1]) / total;
                    entropy += -log2(p) * p;
                }
            }
        }

        snprintf(key, sizeof(key), "lavfi.entropy.entropy.%s.%c", s->mode ? "diff" : "normal", s->planenames[cidx]);
        snprintf(metabuf, sizeof(metabuf), "%f", entropy);
        av_dict_set(&in->metadata, key, metabuf, 0);
        snprintf(key, sizeof(key), "lavfi.entropy.normalized_entropy.%s.%c", s->mode ? "diff" : "normal", s->planenames[cidx]);
        snprintf(metabuf, sizeof(metabuf), "%f", entropy / log2(1 << s->depth));
        av_dict_set(&in->metadata, key, metabuf, 0);
    }

    return ff_filter_frame(outlink, in);
}