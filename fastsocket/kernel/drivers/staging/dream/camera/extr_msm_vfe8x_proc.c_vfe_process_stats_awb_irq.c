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
struct TYPE_4__ {TYPE_1__ awbStatsControl; } ;

/* Variables and functions */
 TYPE_2__* ctrl ; 
 int vfe_get_awb_pingpong_status () ; 
 int /*<<< orphan*/  vfe_read_awb_buf_addr (int) ; 
 int /*<<< orphan*/  vfe_send_awb_stats_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfe_update_awb_buf_addr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_process_stats_awb_irq(void)
{
	boolean bufferAvailable;

	if (!(ctrl->awbStatsControl.ackPending)) {

		ctrl->awbStatsControl.pingPongStatus =
			vfe_get_awb_pingpong_status();

		bufferAvailable = (ctrl->awbStatsControl.pingPongStatus) ^ 1;

		ctrl->awbStatsControl.bufToRender =
			vfe_read_awb_buf_addr(bufferAvailable);

		vfe_update_awb_buf_addr(bufferAvailable,
			ctrl->awbStatsControl.nextFrameAddrBuf);

		vfe_send_awb_stats_msg(ctrl->awbStatsControl.bufToRender);

	} else
		ctrl->awbStatsControl.droppedStatsFrameCount++;
}