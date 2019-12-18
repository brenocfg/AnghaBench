#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {TYPE_2__* priv; } ;
struct TYPE_8__ {size_t format; TYPE_1__* iir; } ;
struct TYPE_7__ {int* nb_ab; void** ab; void** cache; } ;
typedef  TYPE_1__ IIRChannel ;
typedef  TYPE_2__ AudioIIRContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_strdup (int /*<<< orphan*/ *) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  count_coefficients (char*,int*) ; 
 int /*<<< orphan*/ * format ; 
 int read_tf_coefficients (TYPE_3__*,char*,int,void*) ; 
 int read_zp_coefficients (TYPE_3__*,char*,int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_channels(AVFilterContext *ctx, int channels, uint8_t *item_str, int ab)
{
    AudioIIRContext *s = ctx->priv;
    char *p, *arg, *old_str, *prev_arg = NULL, *saveptr = NULL;
    int i, ret;

    p = old_str = av_strdup(item_str);
    if (!p)
        return AVERROR(ENOMEM);
    for (i = 0; i < channels; i++) {
        IIRChannel *iir = &s->iir[i];

        if (!(arg = av_strtok(p, "|", &saveptr)))
            arg = prev_arg;

        if (!arg) {
            av_freep(&old_str);
            return AVERROR(EINVAL);
        }

        count_coefficients(arg, &iir->nb_ab[ab]);

        p = NULL;
        iir->cache[ab] = av_calloc(iir->nb_ab[ab] + 1, sizeof(double));
        iir->ab[ab] = av_calloc(iir->nb_ab[ab] * (!!s->format + 1), sizeof(double));
        if (!iir->ab[ab] || !iir->cache[ab]) {
            av_freep(&old_str);
            return AVERROR(ENOMEM);
        }

        if (s->format) {
            ret = read_zp_coefficients(ctx, arg, iir->nb_ab[ab], iir->ab[ab], format[s->format]);
        } else {
            ret = read_tf_coefficients(ctx, arg, iir->nb_ab[ab], iir->ab[ab]);
        }
        if (ret < 0) {
            av_freep(&old_str);
            return ret;
        }
        prev_arg = arg;
    }

    av_freep(&old_str);

    return 0;
}