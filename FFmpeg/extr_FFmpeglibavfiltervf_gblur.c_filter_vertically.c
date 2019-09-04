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
struct TYPE_5__ {int height; int width; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {float boundaryscaleV; int steps; float nuV; float* buffer; } ;
typedef  TYPE_2__ GBlurContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static int filter_vertically(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    GBlurContext *s = ctx->priv;
    ThreadData *td = arg;
    const int height = td->height;
    const int width = td->width;
    const int slice_start = (width *  jobnr   ) / nb_jobs;
    const int slice_end   = (width * (jobnr+1)) / nb_jobs;
    const float boundaryscale = s->boundaryscaleV;
    const int numpixels = width * height;
    const int steps = s->steps;
    const float nu = s->nuV;
    float *buffer = s->buffer;
    int i, x, step;
    float *ptr;

    /* Filter vertically along each column */
    for (x = slice_start; x < slice_end; x++) {
        for (step = 0; step < steps; step++) {
            ptr = buffer + x;
            ptr[0] *= boundaryscale;

            /* Filter downwards */
            for (i = width; i < numpixels; i += width)
                ptr[i] += nu * ptr[i - width];

            ptr[i = numpixels - width] *= boundaryscale;

            /* Filter upwards */
            for (; i > 0; i -= width)
                ptr[i - width] += nu * ptr[i];
        }
    }

    return 0;
}