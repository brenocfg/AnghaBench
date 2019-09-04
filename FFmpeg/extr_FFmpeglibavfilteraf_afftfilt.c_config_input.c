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
struct TYPE_9__ {int fft_bits; int window_size; int* window_func_lut; int overlap; int hop_size; int /*<<< orphan*/  buffer; scalar_t__ win_scale; int /*<<< orphan*/  win_func; int /*<<< orphan*/  fifo; int /*<<< orphan*/ * imag; scalar_t__ real_str; scalar_t__ img_str; int /*<<< orphan*/  nb_exprs; int /*<<< orphan*/ * real; void** fft_temp; void** fft_data; void* ifft; void* fft; int /*<<< orphan*/  pts; } ;
struct TYPE_8__ {TYPE_3__* priv; } ;
struct TYPE_7__ {int channels; int /*<<< orphan*/  format; TYPE_2__* dst; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;
typedef  TYPE_3__ AFFTFiltContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_audio_fifo_alloc (int /*<<< orphan*/ ,int,int) ; 
 void* av_calloc (int,int) ; 
 int av_expr_parse (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* av_fft_init (int,int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int* av_realloc_f (int*,int,int) ; 
 char* av_strdup (scalar_t__) ; 
 char* av_strtok (char*,char*,char**) ; 
 int /*<<< orphan*/  ff_get_audio_buffer (TYPE_1__*,int) ; 
 int /*<<< orphan*/  func2 ; 
 int /*<<< orphan*/  func2_names ; 
 int /*<<< orphan*/  generate_window_func (int*,int,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AFFTFiltContext *s = ctx->priv;
    char *saveptr = NULL;
    int ret = 0, ch, i;
    float overlap;
    char *args;
    const char *last_expr = "1";

    s->pts  = AV_NOPTS_VALUE;
    s->fft  = av_fft_init(s->fft_bits, 0);
    s->ifft = av_fft_init(s->fft_bits, 1);
    if (!s->fft || !s->ifft)
        return AVERROR(ENOMEM);

    s->window_size = 1 << s->fft_bits;

    s->fft_data = av_calloc(inlink->channels, sizeof(*s->fft_data));
    if (!s->fft_data)
        return AVERROR(ENOMEM);

    s->fft_temp = av_calloc(inlink->channels, sizeof(*s->fft_temp));
    if (!s->fft_temp)
        return AVERROR(ENOMEM);

    for (ch = 0; ch < inlink->channels; ch++) {
        s->fft_data[ch] = av_calloc(s->window_size, sizeof(**s->fft_data));
        if (!s->fft_data[ch])
            return AVERROR(ENOMEM);
    }

    for (ch = 0; ch < inlink->channels; ch++) {
        s->fft_temp[ch] = av_calloc(s->window_size, sizeof(**s->fft_temp));
        if (!s->fft_temp[ch])
            return AVERROR(ENOMEM);
    }

    s->real = av_calloc(inlink->channels, sizeof(*s->real));
    if (!s->real)
        return AVERROR(ENOMEM);

    s->imag = av_calloc(inlink->channels, sizeof(*s->imag));
    if (!s->imag)
        return AVERROR(ENOMEM);

    args = av_strdup(s->real_str);
    if (!args)
        return AVERROR(ENOMEM);

    for (ch = 0; ch < inlink->channels; ch++) {
        char *arg = av_strtok(ch == 0 ? args : NULL, "|", &saveptr);

        ret = av_expr_parse(&s->real[ch], arg ? arg : last_expr, var_names,
                            NULL, NULL, func2_names, func2, 0, ctx);
        if (ret < 0)
            break;
        if (arg)
            last_expr = arg;
        s->nb_exprs++;
    }

    av_free(args);

    args = av_strdup(s->img_str ? s->img_str : s->real_str);
    if (!args)
        return AVERROR(ENOMEM);

    for (ch = 0; ch < inlink->channels; ch++) {
        char *arg = av_strtok(ch == 0 ? args : NULL, "|", &saveptr);

        ret = av_expr_parse(&s->imag[ch], arg ? arg : last_expr, var_names,
                            NULL, NULL, func2_names, func2, 0, ctx);
        if (ret < 0)
            break;
        if (arg)
            last_expr = arg;
    }

    av_free(args);

    s->fifo = av_audio_fifo_alloc(inlink->format, inlink->channels, s->window_size);
    if (!s->fifo)
        return AVERROR(ENOMEM);

    s->window_func_lut = av_realloc_f(s->window_func_lut, s->window_size,
                                      sizeof(*s->window_func_lut));
    if (!s->window_func_lut)
        return AVERROR(ENOMEM);
    generate_window_func(s->window_func_lut, s->window_size, s->win_func, &overlap);
    if (s->overlap == 1)
        s->overlap = overlap;

    for (s->win_scale = 0, i = 0; i < s->window_size; i++) {
        s->win_scale += s->window_func_lut[i] * s->window_func_lut[i];
    }

    s->hop_size = s->window_size * (1 - s->overlap);
    if (s->hop_size <= 0)
        return AVERROR(EINVAL);

    s->buffer = ff_get_audio_buffer(inlink, s->window_size * 2);
    if (!s->buffer)
        return AVERROR(ENOMEM);

    return ret;
}