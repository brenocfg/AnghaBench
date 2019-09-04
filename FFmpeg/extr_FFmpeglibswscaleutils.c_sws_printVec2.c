#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; double* coeff; } ;
typedef  TYPE_1__ SwsVector ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int,char*,...) ; 

void sws_printVec2(SwsVector *a, AVClass *log_ctx, int log_level)
{
    int i;
    double max = 0;
    double min = 0;
    double range;

    for (i = 0; i < a->length; i++)
        if (a->coeff[i] > max)
            max = a->coeff[i];

    for (i = 0; i < a->length; i++)
        if (a->coeff[i] < min)
            min = a->coeff[i];

    range = max - min;

    for (i = 0; i < a->length; i++) {
        int x = (int)((a->coeff[i] - min) * 60.0 / range + 0.5);
        av_log(log_ctx, log_level, "%1.3f ", a->coeff[i]);
        for (; x > 0; x--)
            av_log(log_ctx, log_level, " ");
        av_log(log_ctx, log_level, "|\n");
    }
}