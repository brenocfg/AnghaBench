#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean ;
struct TYPE_3__ {int pingPongStatus; int /*<<< orphan*/  droppedStatsFrameCount; int /*<<< orphan*/  bufToRender; int /*<<< orphan*/  nextFrameAddrBuf; int /*<<< orphan*/  ackPending; } ;
struct TYPE_4__ {TYPE_1__ afStatsControl; } ;

/* Variables and functions */
 TYPE_2__* ctrl ; 
 int vfe_get_af_pingpong_status () ; 
 int /*<<< orphan*/  vfe_read_af_buf_addr (int) ; 
 int /*<<< orphan*/  vfe_send_af_stats_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_update_af_buf_addr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_process_stats_af_irq(void)
{
	boolean bufferAvailable;

	if (!(ctrl->afStatsControl.ackPending)) {

		/* read hardware status. */
		ctrl->afStatsControl.pingPongStatus =
			vfe_get_af_pingpong_status();

		bufferAvailable =
			(ctrl->afStatsControl.pingPongStatus) ^ 1;

		ctrl->afStatsControl.bufToRender =
			vfe_read_af_buf_addr(bufferAvailable);

		/* update the same buffer address (ping or pong) */
		vfe_update_af_buf_addr(bufferAvailable,
			ctrl->afStatsControl.nextFrameAddrBuf);

		vfe_send_af_stats_msg(ctrl->afStatsControl.bufToRender);
	} else
		ctrl->afStatsControl.droppedStatsFrameCount++;
}