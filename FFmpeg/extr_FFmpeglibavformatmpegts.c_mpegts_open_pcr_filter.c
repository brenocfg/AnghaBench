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
typedef  int /*<<< orphan*/  MpegTSFilter ;
typedef  int /*<<< orphan*/  MpegTSContext ;

/* Variables and functions */
 int /*<<< orphan*/  MPEGTS_PCR ; 
 int /*<<< orphan*/ * mpegts_open_filter (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MpegTSFilter *mpegts_open_pcr_filter(MpegTSContext *ts, unsigned int pid)
{
    return mpegts_open_filter(ts, pid, MPEGTS_PCR);
}