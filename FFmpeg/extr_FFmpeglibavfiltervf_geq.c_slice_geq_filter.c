#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint16_t ;
struct TYPE_6__ {int height; int width; int plane; int linesize; } ;
typedef  TYPE_1__ ThreadData ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {double* values; int bps; int /*<<< orphan*/ * e; void** dst16; void** dst; } ;
typedef  TYPE_2__ GEQContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 size_t VAR_H ; 
 size_t VAR_N ; 
 size_t VAR_SH ; 
 size_t VAR_SW ; 
 size_t VAR_T ; 
 int VAR_VARS_NB ; 
 size_t VAR_W ; 
 size_t VAR_X ; 
 size_t VAR_Y ; 
 void* av_expr_eval (int /*<<< orphan*/ ,double*,TYPE_2__*) ; 

__attribute__((used)) static int slice_geq_filter(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    GEQContext *geq = ctx->priv;
    ThreadData *td = arg;
    const int height = td->height;
    const int width = td->width;
    const int plane = td->plane;
    const int linesize = td->linesize;
    const int slice_start = (height *  jobnr) / nb_jobs;
    const int slice_end = (height * (jobnr+1)) / nb_jobs;
    int x, y;
    uint8_t *ptr;
    uint16_t *ptr16;

    double values[VAR_VARS_NB];
    values[VAR_W] = geq->values[VAR_W];
    values[VAR_H] = geq->values[VAR_H];
    values[VAR_N] = geq->values[VAR_N];
    values[VAR_SW] = geq->values[VAR_SW];
    values[VAR_SH] = geq->values[VAR_SH];
    values[VAR_T] = geq->values[VAR_T];

    if (geq->bps == 8) {
        for (y = slice_start; y < slice_end; y++) {
            ptr = geq->dst + linesize * y;
            values[VAR_Y] = y;

            for (x = 0; x < width; x++) {
                values[VAR_X] = x;
                ptr[x] = av_expr_eval(geq->e[plane], values, geq);
            }
            ptr += linesize;
        }
    }
    else {
        for (y = slice_start; y < slice_end; y++) {
            ptr16 = geq->dst16 + (linesize/2) * y;
            values[VAR_Y] = y;
            for (x = 0; x < width; x++) {
                values[VAR_X] = x;
                ptr16[x] = av_expr_eval(geq->e[plane], values, geq);
            }
        }
    }

    return 0;
}