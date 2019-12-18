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
 int /*<<< orphan*/  do_vertical_columns (float*,int const,int const,int const,int const,int const,float const,float const,int) ; 

__attribute__((used)) static int filter_vertically(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    GBlurContext *s = ctx->priv;
    ThreadData *td = arg;
    const int height = td->height;
    const int width = td->width;
    const int slice_start = (width *  jobnr   ) / nb_jobs;
    const int slice_end   = (width * (jobnr+1)) / nb_jobs;
    const float boundaryscale = s->boundaryscaleV;
    const int steps = s->steps;
    const float nu = s->nuV;
    float *buffer = s->buffer;
    int aligned_end;

    aligned_end = slice_start + (((slice_end - slice_start) >> 3) << 3);
    /* Filter vertically along columns (process 8 columns in each step) */
    do_vertical_columns(buffer, width, height, slice_start, aligned_end,
                        steps, nu, boundaryscale, 8);

    /* Filter un-aligned columns one by one */
    do_vertical_columns(buffer, width, height, aligned_end, slice_end,
                        steps, nu, boundaryscale, 1);
    return 0;
}