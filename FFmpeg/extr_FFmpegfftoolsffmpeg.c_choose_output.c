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
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {scalar_t__ unavailable; int /*<<< orphan*/  finished; int /*<<< orphan*/  inputs_done; int /*<<< orphan*/  initialized; TYPE_1__* st; } ;
struct TYPE_5__ {scalar_t__ cur_dts; int /*<<< orphan*/  id; int /*<<< orphan*/  index; int /*<<< orphan*/  time_base; } ;
typedef  TYPE_2__ OutputStream ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nb_output_streams ; 
 TYPE_2__** output_streams ; 

__attribute__((used)) static OutputStream *choose_output(void)
{
    int i;
    int64_t opts_min = INT64_MAX;
    OutputStream *ost_min = NULL;

    for (i = 0; i < nb_output_streams; i++) {
        OutputStream *ost = output_streams[i];
        int64_t opts = ost->st->cur_dts == AV_NOPTS_VALUE ? INT64_MIN :
                       av_rescale_q(ost->st->cur_dts, ost->st->time_base,
                                    AV_TIME_BASE_Q);
        if (ost->st->cur_dts == AV_NOPTS_VALUE)
            av_log(NULL, AV_LOG_DEBUG,
                "cur_dts is invalid st:%d (%d) [init:%d i_done:%d finish:%d] (this is harmless if it occurs once at the start per stream)\n",
                ost->st->index, ost->st->id, ost->initialized, ost->inputs_done, ost->finished);

        if (!ost->initialized && !ost->inputs_done)
            return ost;

        if (!ost->finished && opts < opts_min) {
            opts_min = opts;
            ost_min  = ost->unavailable ? NULL : ost;
        }
    }
    return ost_min;
}