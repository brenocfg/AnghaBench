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
struct pvr2_ioread {int enabled; int sync_state; scalar_t__ spigot_open; scalar_t__ sync_buf_offs; scalar_t__ sync_trashed_count; scalar_t__ sync_key_len; scalar_t__ stream_running; scalar_t__ c_data_offs; scalar_t__ c_data_len; int /*<<< orphan*/ * c_data_ptr; int /*<<< orphan*/ * c_buf; int /*<<< orphan*/  stream; } ;
struct pvr2_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_DATA_FLOW ; 
 int /*<<< orphan*/  PVR2_TRACE_START_STOP ; 
 int pvr2_buffer_queue (struct pvr2_buffer*) ; 
 int /*<<< orphan*/  pvr2_ioread_stop (struct pvr2_ioread*) ; 
 struct pvr2_buffer* pvr2_stream_get_idle_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int pvr2_ioread_start(struct pvr2_ioread *cp)
{
	int stat;
	struct pvr2_buffer *bp;
	if (cp->enabled) return 0;
	if (!(cp->stream)) return 0;
	pvr2_trace(PVR2_TRACE_START_STOP,
		   "/*---TRACE_READ---*/ pvr2_ioread_start id=%p",cp);
	while ((bp = pvr2_stream_get_idle_buffer(cp->stream)) != NULL) {
		stat = pvr2_buffer_queue(bp);
		if (stat < 0) {
			pvr2_trace(PVR2_TRACE_DATA_FLOW,
				   "/*---TRACE_READ---*/"
				   " pvr2_ioread_start id=%p"
				   " error=%d",
				   cp,stat);
			pvr2_ioread_stop(cp);
			return stat;
		}
	}
	cp->enabled = !0;
	cp->c_buf = NULL;
	cp->c_data_ptr = NULL;
	cp->c_data_len = 0;
	cp->c_data_offs = 0;
	cp->stream_running = 0;
	if (cp->sync_key_len) {
		pvr2_trace(PVR2_TRACE_DATA_FLOW,
			   "/*---TRACE_READ---*/ sync_state <== 1");
		cp->sync_state = 1;
		cp->sync_trashed_count = 0;
		cp->sync_buf_offs = 0;
	}
	cp->spigot_open = 0;
	return 0;
}