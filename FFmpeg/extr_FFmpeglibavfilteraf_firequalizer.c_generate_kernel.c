#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_13__ {double channels; double channel_layout; double sample_rate; } ;
struct TYPE_12__ {scalar_t__ scale; scalar_t__ gain_entry_err; float* dump_buf; float* kernel_tmp_buf; int rdft_len; double* analysis_buf; int analysis_rdft_len; int fir_len; int wfunc; float* kernel_buf; scalar_t__ multi; scalar_t__ min_phase; int /*<<< orphan*/  rdft; int /*<<< orphan*/  analysis_irdft; scalar_t__ dumpfile; int /*<<< orphan*/  analysis_rdft; scalar_t__ nb_gain_entry; } ;
typedef  TYPE_1__ FIREqualizerContext ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVExpr ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int M_PI ; 
 scalar_t__ SCALE_LINLOG ; 
 scalar_t__ SCALE_LOGLIN ; 
 scalar_t__ SCALE_LOGLOG ; 
 size_t VAR_CH ; 
 size_t VAR_CHID ; 
 size_t VAR_CHLAYOUT ; 
 size_t VAR_CHS ; 
 size_t VAR_F ; 
 int VAR_NB ; 
 size_t VAR_SR ; 
#define  WFUNC_BHARRIS 137 
#define  WFUNC_BLACKMAN 136 
#define  WFUNC_BNUTTALL 135 
#define  WFUNC_HAMMING 134 
#define  WFUNC_HANN 133 
#define  WFUNC_MNUTTALL3 132 
#define  WFUNC_NUTTALL 131 
#define  WFUNC_NUTTALL3 130 
#define  WFUNC_RECTANGULAR 129 
#define  WFUNC_TUKEY 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 double av_channel_layout_extract_channel (double,int) ; 
 double av_expr_eval (int /*<<< orphan*/ *,double*,TYPE_3__*) ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int av_expr_parse (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char const**,double (*) (void*,double),int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int av_expr_parse_and_eval (double*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,double (*) (void*,double,double),TYPE_3__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,float*) ; 
 double cos (int) ; 
 int /*<<< orphan*/  cubic_interpolate_func ; 
 int /*<<< orphan*/  dump_fir (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  entry_func ; 
 double fabs (double) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 int /*<<< orphan*/  gain_interpolate_func ; 
 int /*<<< orphan*/  generate_min_phase_kernel (TYPE_1__*,float*) ; 
 scalar_t__ isinf (float) ; 
 scalar_t__ isnan (float) ; 
 double log2 (double) ; 
 int /*<<< orphan*/  memcpy (float*,double*,int) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 
 double pow (double,double) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int generate_kernel(AVFilterContext *ctx, const char *gain, const char *gain_entry)
{
    FIREqualizerContext *s = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];
    const char *gain_entry_func_names[] = { "entry", NULL };
    const char *gain_func_names[] = { "gain_interpolate", "cubic_interpolate", NULL };
    double (*gain_entry_funcs[])(void *, double, double) = { entry_func, NULL };
    double (*gain_funcs[])(void *, double) = { gain_interpolate_func, cubic_interpolate_func, NULL };
    double vars[VAR_NB];
    AVExpr *gain_expr;
    int ret, k, center, ch;
    int xlog = s->scale == SCALE_LOGLIN || s->scale == SCALE_LOGLOG;
    int ylog = s->scale == SCALE_LINLOG || s->scale == SCALE_LOGLOG;
    FILE *dump_fp = NULL;

    s->nb_gain_entry = 0;
    s->gain_entry_err = 0;
    if (gain_entry) {
        double result = 0.0;
        ret = av_expr_parse_and_eval(&result, gain_entry, NULL, NULL, NULL, NULL,
                                     gain_entry_func_names, gain_entry_funcs, ctx, 0, ctx);
        if (ret < 0)
            return ret;
        if (s->gain_entry_err < 0)
            return s->gain_entry_err;
    }

    av_log(ctx, AV_LOG_DEBUG, "nb_gain_entry = %d.\n", s->nb_gain_entry);

    ret = av_expr_parse(&gain_expr, gain, var_names,
                        gain_func_names, gain_funcs, NULL, NULL, 0, ctx);
    if (ret < 0)
        return ret;

    if (s->dumpfile && (!s->dump_buf || !s->analysis_rdft || !(dump_fp = fopen(s->dumpfile, "w"))))
        av_log(ctx, AV_LOG_WARNING, "dumping failed.\n");

    vars[VAR_CHS] = inlink->channels;
    vars[VAR_CHLAYOUT] = inlink->channel_layout;
    vars[VAR_SR] = inlink->sample_rate;
    for (ch = 0; ch < inlink->channels; ch++) {
        float *rdft_buf = s->kernel_tmp_buf + ch * s->rdft_len;
        double result;
        vars[VAR_CH] = ch;
        vars[VAR_CHID] = av_channel_layout_extract_channel(inlink->channel_layout, ch);
        vars[VAR_F] = 0.0;
        if (xlog)
            vars[VAR_F] = log2(0.05 * vars[VAR_F]);
        result = av_expr_eval(gain_expr, vars, ctx);
        s->analysis_buf[0] = ylog ? pow(10.0, 0.05 * result) : result;

        vars[VAR_F] = 0.5 * inlink->sample_rate;
        if (xlog)
            vars[VAR_F] = log2(0.05 * vars[VAR_F]);
        result = av_expr_eval(gain_expr, vars, ctx);
        s->analysis_buf[1] = ylog ? pow(10.0, 0.05 * result) : result;

        for (k = 1; k < s->analysis_rdft_len/2; k++) {
            vars[VAR_F] = k * ((double)inlink->sample_rate /(double)s->analysis_rdft_len);
            if (xlog)
                vars[VAR_F] = log2(0.05 * vars[VAR_F]);
            result = av_expr_eval(gain_expr, vars, ctx);
            s->analysis_buf[2*k] = ylog ? pow(10.0, 0.05 * result) : s->min_phase ? fabs(result) : result;
            s->analysis_buf[2*k+1] = 0.0;
        }

        if (s->dump_buf)
            memcpy(s->dump_buf, s->analysis_buf, s->analysis_rdft_len * sizeof(*s->analysis_buf));

        av_rdft_calc(s->analysis_irdft, s->analysis_buf);
        center = s->fir_len / 2;

        for (k = 0; k <= center; k++) {
            double u = k * (M_PI/center);
            double win;
            switch (s->wfunc) {
            case WFUNC_RECTANGULAR:
                win = 1.0;
                break;
            case WFUNC_HANN:
                win = 0.5 + 0.5 * cos(u);
                break;
            case WFUNC_HAMMING:
                win = 0.53836 + 0.46164 * cos(u);
                break;
            case WFUNC_BLACKMAN:
                win = 0.42 + 0.5 * cos(u) + 0.08 * cos(2*u);
                break;
            case WFUNC_NUTTALL3:
                win = 0.40897 + 0.5 * cos(u) + 0.09103 * cos(2*u);
                break;
            case WFUNC_MNUTTALL3:
                win = 0.4243801 + 0.4973406 * cos(u) + 0.0782793 * cos(2*u);
                break;
            case WFUNC_NUTTALL:
                win = 0.355768 + 0.487396 * cos(u) + 0.144232 * cos(2*u) + 0.012604 * cos(3*u);
                break;
            case WFUNC_BNUTTALL:
                win = 0.3635819 + 0.4891775 * cos(u) + 0.1365995 * cos(2*u) + 0.0106411 * cos(3*u);
                break;
            case WFUNC_BHARRIS:
                win = 0.35875 + 0.48829 * cos(u) + 0.14128 * cos(2*u) + 0.01168 * cos(3*u);
                break;
            case WFUNC_TUKEY:
                win = (u <= 0.5 * M_PI) ? 1.0 : (0.5 + 0.5 * cos(2*u - M_PI));
                break;
            default:
                av_assert0(0);
            }
            s->analysis_buf[k] *= (2.0/s->analysis_rdft_len) * (2.0/s->rdft_len) * win;
            if (k)
                s->analysis_buf[s->analysis_rdft_len - k] = s->analysis_buf[k];
        }

        memset(s->analysis_buf + center + 1, 0, (s->analysis_rdft_len - s->fir_len) * sizeof(*s->analysis_buf));
        memcpy(rdft_buf, s->analysis_buf, s->rdft_len/2 * sizeof(*s->analysis_buf));
        memcpy(rdft_buf + s->rdft_len/2, s->analysis_buf + s->analysis_rdft_len - s->rdft_len/2, s->rdft_len/2 * sizeof(*s->analysis_buf));
        if (s->min_phase)
            generate_min_phase_kernel(s, rdft_buf);
        av_rdft_calc(s->rdft, rdft_buf);

        for (k = 0; k < s->rdft_len; k++) {
            if (isnan(rdft_buf[k]) || isinf(rdft_buf[k])) {
                av_log(ctx, AV_LOG_ERROR, "filter kernel contains nan or infinity.\n");
                av_expr_free(gain_expr);
                if (dump_fp)
                    fclose(dump_fp);
                return AVERROR(EINVAL);
            }
        }

        if (!s->min_phase) {
            rdft_buf[s->rdft_len-1] = rdft_buf[1];
            for (k = 0; k < s->rdft_len/2; k++)
                rdft_buf[k] = rdft_buf[2*k];
            rdft_buf[s->rdft_len/2] = rdft_buf[s->rdft_len-1];
        }

        if (dump_fp)
            dump_fir(ctx, dump_fp, ch);

        if (!s->multi)
            break;
    }

    memcpy(s->kernel_buf, s->kernel_tmp_buf, (s->multi ? inlink->channels : 1) * s->rdft_len * sizeof(*s->kernel_buf));
    av_expr_free(gain_expr);
    if (dump_fp)
        fclose(dump_fp);
    return 0;
}