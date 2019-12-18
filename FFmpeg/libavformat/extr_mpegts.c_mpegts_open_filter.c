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
typedef  enum MpegTSFilterType { ____Placeholder_MpegTSFilterType } MpegTSFilterType ;
struct TYPE_7__ {TYPE_1__** pids; int /*<<< orphan*/  stream; } ;
struct TYPE_6__ {int type; unsigned int pid; int es_id; int last_cc; int last_pcr; } ;
typedef  TYPE_1__ MpegTSFilter ;
typedef  TYPE_2__ MpegTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 unsigned int NB_PID_MAX ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 TYPE_1__* av_mallocz (int) ; 

__attribute__((used)) static MpegTSFilter *mpegts_open_filter(MpegTSContext *ts, unsigned int pid,
                                        enum MpegTSFilterType type)
{
    MpegTSFilter *filter;

    av_log(ts->stream, AV_LOG_TRACE, "Filter: pid=0x%x type=%d\n", pid, type);

    if (pid >= NB_PID_MAX || ts->pids[pid])
        return NULL;
    filter = av_mallocz(sizeof(MpegTSFilter));
    if (!filter)
        return NULL;
    ts->pids[pid] = filter;

    filter->type    = type;
    filter->pid     = pid;
    filter->es_id   = -1;
    filter->last_cc = -1;
    filter->last_pcr= -1;

    return filter;
}