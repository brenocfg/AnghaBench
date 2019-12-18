#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_6__* priv; } ;
struct TYPE_17__ {int channels; int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_16__ {TYPE_5__* offset; TYPE_4__* tmp; TYPE_3__* coeffs; TYPE_2__* delay; TYPE_1__** frame; } ;
struct TYPE_15__ {scalar_t__* extended_data; } ;
struct TYPE_14__ {scalar_t__* extended_data; } ;
struct TYPE_13__ {scalar_t__* extended_data; } ;
struct TYPE_12__ {scalar_t__* extended_data; } ;
struct TYPE_11__ {scalar_t__* extended_data; } ;
typedef  TYPE_6__ AudioNLMSContext ;
typedef  TYPE_7__ AVFrame ;
typedef  TYPE_8__ AVFilterContext ;

/* Variables and functions */
 float process_sample (TYPE_6__*,float const,float const,float*,float*,float*,int*) ; 

__attribute__((used)) static int process_channels(AVFilterContext *ctx, void *arg, int jobnr, int nb_jobs)
{
    AudioNLMSContext *s = ctx->priv;
    AVFrame *out = arg;
    const int start = (out->channels * jobnr) / nb_jobs;
    const int end = (out->channels * (jobnr+1)) / nb_jobs;

    for (int c = start; c < end; c++) {
        const float *input = (const float *)s->frame[0]->extended_data[c];
        const float *desired = (const float *)s->frame[1]->extended_data[c];
        float *delay = (float *)s->delay->extended_data[c];
        float *coeffs = (float *)s->coeffs->extended_data[c];
        float *tmp = (float *)s->tmp->extended_data[c];
        int *offset = (int *)s->offset->extended_data[c];
        float *output = (float *)out->extended_data[c];

        for (int n = 0; n < out->nb_samples; n++)
            output[n] = process_sample(s, input[n], desired[n], delay, coeffs, tmp, offset);
    }

    return 0;
}