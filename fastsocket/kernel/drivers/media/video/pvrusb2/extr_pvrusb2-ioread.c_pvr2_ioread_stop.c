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
struct pvr2_ioread {scalar_t__ sync_state; scalar_t__ spigot_open; scalar_t__ stream_running; scalar_t__ enabled; scalar_t__ c_data_offs; scalar_t__ c_data_len; int /*<<< orphan*/ * c_data_ptr; int /*<<< orphan*/ * c_buf; int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_DATA_FLOW ; 
 int /*<<< orphan*/  PVR2_TRACE_START_STOP ; 
 int /*<<< orphan*/  pvr2_stream_kill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void pvr2_ioread_stop(struct pvr2_ioread *cp)
{
	if (!(cp->enabled)) return;
	pvr2_trace(PVR2_TRACE_START_STOP,
		   "/*---TRACE_READ---*/ pvr2_ioread_stop id=%p",cp);
	pvr2_stream_kill(cp->stream);
	cp->c_buf = NULL;
	cp->c_data_ptr = NULL;
	cp->c_data_len = 0;
	cp->c_data_offs = 0;
	cp->enabled = 0;
	cp->stream_running = 0;
	cp->spigot_open = 0;
	if (cp->sync_state) {
		pvr2_trace(PVR2_TRACE_DATA_FLOW,
			   "/*---TRACE_READ---*/ sync_state <== 0");
		cp->sync_state = 0;
	}
}