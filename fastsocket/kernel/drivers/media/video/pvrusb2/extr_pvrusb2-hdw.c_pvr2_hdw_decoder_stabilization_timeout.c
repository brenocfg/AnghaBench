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
struct pvr2_hdw {int state_decoder_ready; int state_stale; int /*<<< orphan*/  workpoll; int /*<<< orphan*/  workqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_stbit (char*,int) ; 

__attribute__((used)) static void pvr2_hdw_decoder_stabilization_timeout(unsigned long data)
{
	struct pvr2_hdw *hdw = (struct pvr2_hdw *)data;
	hdw->state_decoder_ready = !0;
	trace_stbit("state_decoder_ready", hdw->state_decoder_ready);
	hdw->state_stale = !0;
	queue_work(hdw->workqueue, &hdw->workpoll);
}