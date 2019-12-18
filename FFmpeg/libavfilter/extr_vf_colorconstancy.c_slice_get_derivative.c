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
typedef  double uint8_t ;
struct TYPE_6__ {int* meta_data; double*** data; TYPE_3__* in; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {int* linesize; double** data; } ;
struct TYPE_7__ {int filtersize; double** gauss; int* planeheight; int* planewidth; } ;
typedef  TYPE_2__ ColorConstancyContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int const DIR_X ; 
 scalar_t__ GAUSS (double const*,int,int,int const,int const,int const,double const) ; 
 int GINDX (int const,int) ; 
 size_t INDEX_DIR ; 
 size_t INDEX_DST ; 
 size_t INDEX_ORD ; 
 size_t INDEX_SRC ; 
 size_t INDX2D (int,int,int const) ; 
 int NUM_PLANES ; 

__attribute__((used)) static int slice_get_derivative(AVFilterContext* ctx, void* arg, int jobnr, int nb_jobs)
{
    ColorConstancyContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *in = td->in;
    const int ord = td->meta_data[INDEX_ORD];
    const int dir = td->meta_data[INDEX_DIR];
    const int src_index  = td->meta_data[INDEX_SRC];
    const int dst_index  = td->meta_data[INDEX_DST];
    const int filtersize = s->filtersize;
    const double *gauss  = s->gauss[ord];
    int plane;

    for (plane = 0; plane < NUM_PLANES; ++plane) {
        const int height      = s->planeheight[plane];
        const int width       = s->planewidth[plane];
        const int in_linesize = in->linesize[plane];
        double *dst = td->data[dst_index][plane];
        int slice_start, slice_end;
        int r, c, g;

        if (dir == DIR_X) {
            /** Applying gauss horizontally along each row */
            const uint8_t *src = in->data[plane];
            slice_start = (height * jobnr      ) / nb_jobs;
            slice_end   = (height * (jobnr + 1)) / nb_jobs;

            for (r = slice_start; r < slice_end; ++r) {
                for (c = 0; c < width; ++c) {
                    dst[INDX2D(r, c, width)] = 0;
                    for (g = 0; g < filtersize; ++g) {
                        dst[INDX2D(r, c, width)] += GAUSS(src, r,                        c + GINDX(filtersize, g),
                                                          in_linesize, height, width, gauss[g]);
                    }
                }
            }
        } else {
            /** Applying gauss vertically along each column */
            const double *src = td->data[src_index][plane];
            slice_start = (width * jobnr      ) / nb_jobs;
            slice_end   = (width * (jobnr + 1)) / nb_jobs;

            for (c = slice_start; c < slice_end; ++c) {
                for (r = 0; r < height; ++r) {
                    dst[INDX2D(r, c, width)] = 0;
                    for (g = 0; g < filtersize; ++g) {
                        dst[INDX2D(r, c, width)] += GAUSS(src, r + GINDX(filtersize, g), c,
                                                          width, height, width, gauss[g]);
                    }
                }
            }
        }

    }
    return 0;
}