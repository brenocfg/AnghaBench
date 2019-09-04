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
struct TYPE_6__ {float boundaryscale; int steps; float nu; float* buffer; } ;
typedef  TYPE_2__ GBlurContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static int filter_horizontally(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    GBlurContext *s = ctx->priv;
    ThreadData *td = arg;
    const int height = td->height;
    const int width = td->width;
    const int slice_start = (height *  jobnr   ) / nb_jobs;
    const int slice_end   = (height * (jobnr+1)) / nb_jobs;
    const float boundaryscale = s->boundaryscale;
    const int steps = s->steps;
    const float nu = s->nu;
    float *buffer = s->buffer;
    int y, x, step;
    float *ptr;

    /* Filter horizontally along each row */
    for (y = slice_start; y < slice_end; y++) {
        for (step = 0; step < steps; step++) {
            ptr = buffer + width * y;
            ptr[0] *= boundaryscale;

            /* Filter rightwards */
            for (x = 1; x < width; x++)
                ptr[x] += nu * ptr[x - 1];

            ptr[x = width - 1] *= boundaryscale;

            /* Filter leftwards */
            for (; x > 0; x--)
                ptr[x - 1] += nu * ptr[x];
        }
    }

    return 0;
}