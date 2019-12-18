#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int filtersize; int difford; double sigma; int** gauss; } ;
typedef  TYPE_1__ ColorConstancyContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  ENOMEM ; 
 double GINDX (int,int) ; 
 int M_PI ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int* av_mallocz_array (int,int) ; 
 double exp (int) ; 
 int pow (double,int) ; 
 double sqrt (int) ; 

__attribute__((used)) static int set_gauss(AVFilterContext *ctx)
{
    ColorConstancyContext *s = ctx->priv;
    int filtersize = s->filtersize;
    int difford    = s->difford;
    double sigma   = s->sigma;
    double sum1, sum2;
    int i;

    for (i = 0; i <= difford; ++i) {
        s->gauss[i] = av_mallocz_array(filtersize, sizeof(*s->gauss[i]));
        if (!s->gauss[i]) {
            for (; i >= 0; --i) {
                av_freep(&s->gauss[i]);
            }
            av_log(ctx, AV_LOG_ERROR, "Out of memory while allocating gauss buffers.\n");
            return AVERROR(ENOMEM);
        }
    }

    // Order 0
    av_log(ctx, AV_LOG_TRACE, "Setting 0-d gauss with filtersize = %d.\n", filtersize);
    sum1 = 0.0;
    if (!sigma) {
        s->gauss[0][0] = 1; // Copying data to double instead of convolution
    } else {
        for (i = 0; i < filtersize; ++i) {
            s->gauss[0][i] = exp(- pow(GINDX(filtersize, i), 2.) / (2 * sigma * sigma)) / ( sqrt(2 * M_PI) * sigma );
            sum1 += s->gauss[0][i];
        }
        for (i = 0; i < filtersize; ++i) {
            s->gauss[0][i] /= sum1;
        }
    }
    // Order 1
    if (difford > 0) {
        av_log(ctx, AV_LOG_TRACE, "Setting 1-d gauss with filtersize = %d.\n", filtersize);
        sum1 = 0.0;
        for (i = 0; i < filtersize; ++i) {
            s->gauss[1][i] = - (GINDX(filtersize, i) / pow(sigma, 2)) * s->gauss[0][i];
            sum1 += s->gauss[1][i] * GINDX(filtersize, i);
        }

        for (i = 0; i < filtersize; ++i) {
            s->gauss[1][i] /= sum1;
        }

        // Order 2
        if (difford > 1) {
            av_log(ctx, AV_LOG_TRACE, "Setting 2-d gauss with filtersize = %d.\n", filtersize);
            sum1 = 0.0;
            for (i = 0; i < filtersize; ++i) {
                s->gauss[2][i] = ( pow(GINDX(filtersize, i), 2) / pow(sigma, 4) - 1/pow(sigma, 2) )
                                 * s->gauss[0][i];
                sum1 += s->gauss[2][i];
            }

            sum2 = 0.0;
            for (i = 0; i < filtersize; ++i) {
                s->gauss[2][i] -= sum1 / (filtersize);
                sum2 += (0.5 * GINDX(filtersize, i) * GINDX(filtersize, i) * s->gauss[2][i]);
            }
            for (i = 0; i < filtersize ; ++i) {
                s->gauss[2][i] /= sum2;
            }
        }
    }
    return 0;
}