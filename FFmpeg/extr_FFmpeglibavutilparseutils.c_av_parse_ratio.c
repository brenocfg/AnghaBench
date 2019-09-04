#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 TYPE_1__ av_d2q (double,int) ; 
 int av_expr_parse_and_eval (double*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  av_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int av_parse_ratio(AVRational *q, const char *str, int max,
                   int log_offset, void *log_ctx)
{
    char c;
    int ret;

    if (sscanf(str, "%d:%d%c", &q->num, &q->den, &c) != 2) {
        double d;
        ret = av_expr_parse_and_eval(&d, str, NULL, NULL,
                                     NULL, NULL, NULL, NULL,
                                     NULL, log_offset, log_ctx);
        if (ret < 0)
            return ret;
        *q = av_d2q(d, max);
    } else {
        av_reduce(&q->num, &q->den, q->num, q->den, max);
    }

    return 0;
}