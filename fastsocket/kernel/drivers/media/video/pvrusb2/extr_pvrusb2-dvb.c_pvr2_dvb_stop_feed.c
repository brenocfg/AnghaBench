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
struct dvb_demux_feed {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_DVB_FEED ; 
 int pvr2_dvb_ctrl_feed (struct dvb_demux_feed*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_dvb_stop_feed(struct dvb_demux_feed *dvbdmxfeed)
{
	pvr2_trace(PVR2_TRACE_DVB_FEED, "stop pid: 0x%04x", dvbdmxfeed->pid);
	return pvr2_dvb_ctrl_feed(dvbdmxfeed, 0);
}