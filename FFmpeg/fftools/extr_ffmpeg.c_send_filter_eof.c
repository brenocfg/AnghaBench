#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int nb_filters; int /*<<< orphan*/ * filters; TYPE_1__* st; int /*<<< orphan*/  pts; } ;
struct TYPE_4__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ InputStream ;

/* Variables and functions */
 int AV_ROUND_NEAR_INF ; 
 int AV_ROUND_PASS_MINMAX ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  av_rescale_q_rnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ifilter_send_eof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_filter_eof(InputStream *ist)
{
    int i, ret;
    /* TODO keep pts also in stream time base to avoid converting back */
    int64_t pts = av_rescale_q_rnd(ist->pts, AV_TIME_BASE_Q, ist->st->time_base,
                                   AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX);

    for (i = 0; i < ist->nb_filters; i++) {
        ret = ifilter_send_eof(ist->filters[i], pts);
        if (ret < 0)
            return ret;
    }
    return 0;
}