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
struct TYPE_6__ {float boundaryscale; int steps; float nu; float* buffer; int /*<<< orphan*/  (* horiz_slice ) (float*,int const,int const,int const,float const,float const) ;} ;
typedef  TYPE_2__ GBlurContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  emms_c () ; 
 int /*<<< orphan*/  stub1 (float*,int const,int const,int const,float const,float const) ; 

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

    s->horiz_slice(buffer + width * slice_start, width, slice_end - slice_start,
                   steps, nu, boundaryscale);
    emms_c();
    return 0;
}