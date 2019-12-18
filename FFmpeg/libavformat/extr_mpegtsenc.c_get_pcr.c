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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ first_pcr; int /*<<< orphan*/  mux_rate; } ;
typedef  TYPE_1__ MpegTSWrite ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int PCR_TIME_BASE ; 
 scalar_t__ av_rescale (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t get_pcr(const MpegTSWrite *ts, AVIOContext *pb)
{
    return av_rescale(avio_tell(pb) + 11, 8 * PCR_TIME_BASE, ts->mux_rate) +
           ts->first_pcr;
}