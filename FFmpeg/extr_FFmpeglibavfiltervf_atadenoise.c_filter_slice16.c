#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_6__ {TYPE_2__* out; TYPE_2__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {int size; int mid; int nb_planes; int* planeheight; int* planewidth; int* thra; int* thrb; int planes; scalar_t__* linesize; scalar_t__* data; } ;
struct TYPE_8__ {TYPE_4__* priv; } ;
struct TYPE_7__ {int const* linesize; scalar_t__* data; } ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;
typedef  TYPE_4__ ATADenoiseContext ;

/* Variables and functions */
 unsigned int FFABS (int const) ; 
 int SIZE ; 
 int /*<<< orphan*/  av_image_copy_plane (int /*<<< orphan*/ *,int const,int /*<<< orphan*/ *,int const,int const,int const) ; 

__attribute__((used)) static int filter_slice16(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    ATADenoiseContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    const int size = s->size;
    const int mid = s->mid;
    int p, x, y, i, j;

    for (p = 0; p < s->nb_planes; p++) {
        const int h = s->planeheight[p];
        const int w = s->planewidth[p];
        const int slice_start = (h * jobnr) / nb_jobs;
        const int slice_end = (h * (jobnr+1)) / nb_jobs;
        const uint16_t *src = (uint16_t *)(in->data[p] + slice_start * in->linesize[p]);
        uint16_t *dst = (uint16_t *)(out->data[p] + slice_start * out->linesize[p]);
        const int thra = s->thra[p];
        const int thrb = s->thrb[p];
        const uint8_t **data = (const uint8_t **)s->data[p];
        const int *linesize = (const int *)s->linesize[p];
        const uint16_t *srcf[SIZE];

        if (!((1 << p) & s->planes)) {
            av_image_copy_plane((uint8_t *)dst, out->linesize[p], (uint8_t *)src, in->linesize[p],
                                w * 2, slice_end - slice_start);
            continue;
        }

        for (i = 0; i < s->size; i++)
            srcf[i] = (const uint16_t *)(data[i] + slice_start * linesize[i]);

        for (y = slice_start; y < slice_end; y++) {
            for (x = 0; x < w; x++) {
                const int srcx = src[x];
                unsigned lsumdiff = 0, rsumdiff = 0;
                unsigned ldiff, rdiff;
                unsigned sum = srcx;
                int l = 0, r = 0;
                int srcjx, srcix;

                for (j = mid - 1, i = mid + 1; j >= 0 && i < size; j--, i++) {
                    srcjx = srcf[j][x];

                    ldiff = FFABS(srcx - srcjx);
                    lsumdiff += ldiff;
                    if (ldiff > thra ||
                        lsumdiff > thrb)
                        break;
                    l++;
                    sum += srcjx;

                    srcix = srcf[i][x];

                    rdiff = FFABS(srcx - srcix);
                    rsumdiff += rdiff;
                    if (rdiff > thra ||
                        rsumdiff > thrb)
                        break;
                    r++;
                    sum += srcix;
                }

                dst[x] = sum / (r + l + 1);
            }

            dst += out->linesize[p] / 2;
            src += in->linesize[p] / 2;

            for (i = 0; i < size; i++)
                srcf[i] += linesize[i] / 2;
        }
    }

    return 0;
}