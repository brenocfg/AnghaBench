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
typedef  int /*<<< orphan*/  fmt_str ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  prng; int /*<<< orphan*/  var_values; } ;
typedef  TYPE_1__ DrawTextContext ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FE_ALL_EXCEPT ; 
 int FE_INVALID ; 
 int FE_OVERFLOW ; 
 int FE_UNDERFLOW ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,int) ; 
 int av_expr_parse_and_eval (double*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,char) ; 
 int /*<<< orphan*/  feclearexcept (int /*<<< orphan*/ ) ; 
 int fetestexcept (int) ; 
 int /*<<< orphan*/  fun2 ; 
 int /*<<< orphan*/  fun2_names ; 
 int sscanf (char*,char*,unsigned int*) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int func_eval_expr_int_format(AVFilterContext *ctx, AVBPrint *bp,
                          char *fct, unsigned argc, char **argv, int tag)
{
    DrawTextContext *s = ctx->priv;
    double res;
    int intval;
    int ret;
    unsigned int positions = 0;
    char fmt_str[30] = "%";

    /*
     * argv[0] expression to be converted to `int`
     * argv[1] format: 'x', 'X', 'd' or 'u'
     * argv[2] positions printed (optional)
     */

    ret = av_expr_parse_and_eval(&res, argv[0], var_names, s->var_values,
                                 NULL, NULL, fun2_names, fun2,
                                 &s->prng, 0, ctx);
    if (ret < 0) {
        av_log(ctx, AV_LOG_ERROR,
               "Expression '%s' for the expr text expansion function is not valid\n",
               argv[0]);
        return ret;
    }

    if (!strchr("xXdu", argv[1][0])) {
        av_log(ctx, AV_LOG_ERROR, "Invalid format '%c' specified,"
                " allowed values: 'x', 'X', 'd', 'u'\n", argv[1][0]);
        return AVERROR(EINVAL);
    }

    if (argc == 3) {
        ret = sscanf(argv[2], "%u", &positions);
        if (ret != 1) {
            av_log(ctx, AV_LOG_ERROR, "expr_int_format(): Invalid number of positions"
                    " to print: '%s'\n", argv[2]);
            return AVERROR(EINVAL);
        }
    }

    feclearexcept(FE_ALL_EXCEPT);
    intval = res;
    if ((ret = fetestexcept(FE_INVALID|FE_OVERFLOW|FE_UNDERFLOW))) {
        av_log(ctx, AV_LOG_ERROR, "Conversion of floating-point result to int failed. Control register: 0x%08x. Conversion result: %d\n", ret, intval);
        return AVERROR(EINVAL);
    }

    if (argc == 3)
        av_strlcatf(fmt_str, sizeof(fmt_str), "0%u", positions);
    av_strlcatf(fmt_str, sizeof(fmt_str), "%c", argv[1][0]);

    av_log(ctx, AV_LOG_DEBUG, "Formatting value %f (expr '%s') with spec '%s'\n",
            res, argv[0], fmt_str);

    av_bprintf(bp, fmt_str, intval);

    return 0;
}