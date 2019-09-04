#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {double frame_count_out; } ;
struct TYPE_6__ {double* planewidth; double* planeheight; int* rdft_hlen; int* rdft_vlen; int /*<<< orphan*/ * weight_expr; int /*<<< orphan*/ ** weight; } ;
typedef  TYPE_1__ FFTFILTContext ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 size_t VAR_H ; 
 size_t VAR_N ; 
 int VAR_VARS_NB ; 
 size_t VAR_W ; 
 size_t VAR_X ; 
 size_t VAR_Y ; 
 int /*<<< orphan*/  av_expr_eval (int /*<<< orphan*/ ,double*,TYPE_1__*) ; 

__attribute__((used)) static void do_eval(FFTFILTContext *s, AVFilterLink *inlink, int plane)
{
    double values[VAR_VARS_NB];
    int i, j;

    values[VAR_N] = inlink->frame_count_out;
    values[VAR_W] = s->planewidth[plane];
    values[VAR_H] = s->planeheight[plane];

    for (i = 0; i < s->rdft_hlen[plane]; i++) {
        values[VAR_X] = i;
        for (j = 0; j < s->rdft_vlen[plane]; j++) {
            values[VAR_Y] = j;
            s->weight[plane][i * s->rdft_vlen[plane] + j] =
            av_expr_eval(s->weight_expr[plane], values, s);
        }
    }
}