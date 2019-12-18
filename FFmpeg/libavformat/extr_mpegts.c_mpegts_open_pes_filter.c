#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* opaque; int /*<<< orphan*/ * pes_cb; } ;
struct TYPE_6__ {TYPE_2__ pes_filter; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  PESCallback ;
typedef  TYPE_2__ MpegTSPESFilter ;
typedef  TYPE_3__ MpegTSFilter ;
typedef  int /*<<< orphan*/  MpegTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  MPEGTS_PES ; 
 TYPE_3__* mpegts_open_filter (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MpegTSFilter *mpegts_open_pes_filter(MpegTSContext *ts, unsigned int pid,
                                            PESCallback *pes_cb,
                                            void *opaque)
{
    MpegTSFilter *filter;
    MpegTSPESFilter *pes;

    if (!(filter = mpegts_open_filter(ts, pid, MPEGTS_PES)))
        return NULL;

    pes = &filter->u.pes_filter;
    pes->pes_cb = pes_cb;
    pes->opaque = opaque;
    return filter;
}