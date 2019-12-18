#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVExpr ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_expr_free (int /*<<< orphan*/ *) ; 
 int av_expr_parse (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 char* av_strdup (char const*) ; 
 int /*<<< orphan*/  var_names ; 

__attribute__((used)) static int set_expr(AVExpr **pexpr_ptr, char **expr_ptr,
                    const char *expr, const char *option, void *log_ctx)
{
    int ret;
    AVExpr *new_pexpr;
    char *new_expr;

    new_expr = av_strdup(expr);
    if (!new_expr)
        return AVERROR(ENOMEM);
    ret = av_expr_parse(&new_pexpr, expr, var_names,
                        NULL, NULL, NULL, NULL, 0, log_ctx);
    if (ret < 0) {
        av_log(log_ctx, AV_LOG_ERROR,
               "Error when evaluating the expression '%s' for %s\n",
               expr, option);
        av_free(new_expr);
        return ret;
    }

    if (*pexpr_ptr)
        av_expr_free(*pexpr_ptr);
    *pexpr_ptr = new_pexpr;
    av_freep(expr_ptr);
    *expr_ptr = new_expr;

    return 0;
}