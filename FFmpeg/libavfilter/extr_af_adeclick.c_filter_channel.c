#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_8__* out; } ;
typedef  TYPE_5__ ThreadData ;
struct TYPE_22__ {TYPE_7__* priv; } ;
struct TYPE_21__ {scalar_t__* extended_data; } ;
struct TYPE_20__ {double* window_func_lut; int window_size; int (* detector ) (TYPE_7__*,TYPE_6__*,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,double const*,double*) ;scalar_t__ method; int overlap_skip; int hop_size; scalar_t__ ar_order; TYPE_6__* chan; TYPE_4__* buffer; TYPE_3__* out; TYPE_2__* is; TYPE_1__* in; } ;
struct TYPE_19__ {double* interpolated; int* index; int /*<<< orphan*/  auxiliary; int /*<<< orphan*/  acoefficients; int /*<<< orphan*/  click; int /*<<< orphan*/  detection; int /*<<< orphan*/  tmp; int /*<<< orphan*/  acorrelation; } ;
struct TYPE_17__ {scalar_t__* extended_data; } ;
struct TYPE_16__ {scalar_t__* extended_data; } ;
struct TYPE_15__ {scalar_t__* extended_data; } ;
struct TYPE_14__ {scalar_t__* extended_data; } ;
typedef  TYPE_6__ DeclickChannel ;
typedef  TYPE_7__ AudioDeclickContext ;
typedef  TYPE_8__ AVFrame ;
typedef  TYPE_9__ AVFilterContext ;

/* Variables and functions */
 double autoregression (double const*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int interpolation (TYPE_6__*,double const*,scalar_t__,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,double*) ; 
 scalar_t__ isfinite_array (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (double*,double const*,int) ; 
 int /*<<< orphan*/  memmove (double*,double*,int) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 
 int stub1 (TYPE_7__*,TYPE_6__*,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,double const*,double*) ; 

__attribute__((used)) static int filter_channel(AVFilterContext *ctx, void *arg, int ch, int nb_jobs)
{
    AudioDeclickContext *s = ctx->priv;
    ThreadData *td = arg;
    AVFrame *out = td->out;
    const double *src = (const double *)s->in->extended_data[ch];
    double *is = (double *)s->is->extended_data[ch];
    double *dst = (double *)s->out->extended_data[ch];
    double *ptr = (double *)out->extended_data[ch];
    double *buf = (double *)s->buffer->extended_data[ch];
    const double *w = s->window_func_lut;
    DeclickChannel *c = &s->chan[ch];
    double sigmae;
    int j, ret;

    sigmae = autoregression(src, s->ar_order, s->window_size, c->acoefficients, c->acorrelation, c->tmp);

    if (isfinite_array(c->acoefficients, s->ar_order + 1)) {
        double *interpolated = c->interpolated;
        int *index = c->index;
        int nb_errors;

        nb_errors = s->detector(s, c, sigmae, c->detection, c->acoefficients,
                                c->click, index, src, dst);
        if (nb_errors > 0) {
            ret = interpolation(c, src, s->ar_order, c->acoefficients, index,
                                nb_errors, c->auxiliary, interpolated);
            if (ret < 0)
                return ret;

            for (j = 0; j < nb_errors; j++) {
                dst[index[j]] = interpolated[j];
                is[index[j]] = 1;
            }
        }
    } else {
        memcpy(dst, src, s->window_size * sizeof(*dst));
    }

    if (s->method == 0) {
        for (j = 0; j < s->window_size; j++)
            buf[j] += dst[j] * w[j];
    } else {
        const int skip = s->overlap_skip;

        for (j = 0; j < s->hop_size; j++)
            buf[j] = dst[skip + j];
    }
    for (j = 0; j < s->hop_size; j++)
        ptr[j] = buf[j];

    memmove(buf, buf + s->hop_size, (s->window_size * 2 - s->hop_size) * sizeof(*buf));
    memmove(is, is + s->hop_size, (s->window_size - s->hop_size) * sizeof(*is));
    memset(buf + s->window_size * 2 - s->hop_size, 0, s->hop_size * sizeof(*buf));
    memset(is + s->window_size - s->hop_size, 0, s->hop_size * sizeof(*is));

    return 0;
}