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
typedef  int const int64_t ;
struct TYPE_5__ {double*** data; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {int difford; int* planeheight; int* planewidth; } ;
typedef  TYPE_2__ ColorConstancyContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 size_t INDEX_DX ; 
 size_t INDEX_DXY ; 
 size_t INDEX_DY ; 
 size_t INDEX_NORM ; 
 int NUM_PLANES ; 
 int pow (double const,int) ; 
 double sqrt (int) ; 

__attribute__((used)) static int slice_normalize(AVFilterContext* ctx, void* arg, int jobnr, int nb_jobs)
{
    ColorConstancyContext *s = ctx->priv;
    ThreadData *td = arg;
    const int difford = s->difford;
    int plane;

    for (plane = 0; plane < NUM_PLANES; ++plane) {
        const int height = s->planeheight[plane];
        const int width  = s->planewidth[plane];
        const int64_t numpixels = width * (int64_t)height;
        const int slice_start   = (numpixels * jobnr    ) / nb_jobs;
        const int slice_end     = (numpixels * (jobnr+1)) / nb_jobs;
        const double *dx = td->data[INDEX_DX][plane];
        const double *dy = td->data[INDEX_DY][plane];
        double *norm = td->data[INDEX_NORM][plane];
        int i;

        if (difford == 1) {
            for (i = slice_start; i < slice_end; ++i) {
                norm[i] = sqrt( pow(dx[i], 2) + pow(dy[i], 2));
            }
        } else {
            const double *dxy = td->data[INDEX_DXY][plane];
            for (i = slice_start; i < slice_end; ++i) {
                norm[i] = sqrt( pow(dx[i], 2) + 4 * pow(dxy[i], 2) + pow(dy[i], 2) );
            }
        }
    }

    return 0;
}