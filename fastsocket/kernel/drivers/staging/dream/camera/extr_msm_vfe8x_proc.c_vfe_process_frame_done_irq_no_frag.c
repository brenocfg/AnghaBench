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
typedef  int /*<<< orphan*/  uint32_t ;
struct vfe_output_path_combo {int whichOutputPath; int /*<<< orphan*/  snapshotPendingCount; int /*<<< orphan*/  nextFrameAddrBuf; int /*<<< orphan*/  ackPending; } ;
struct TYPE_3__ {int /*<<< orphan*/  output2Count; int /*<<< orphan*/  output1Count; } ;
struct TYPE_4__ {scalar_t__ vfeOperationMode; TYPE_1__ vfeDroppedFrameCounts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDBG (char*) ; 
 TYPE_2__* ctrl ; 
 int /*<<< orphan*/  vfe_process_frame_done_irq_no_frag_io (struct vfe_output_path_combo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfe_send_output_msg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfe_process_frame_done_irq_no_frag(
	struct vfe_output_path_combo *in)
{
	uint32_t addressToRender[2];
	static uint32_t fcnt;

	if (fcnt++ < 3)
		return;

	if (!in->ackPending) {
		vfe_process_frame_done_irq_no_frag_io(in,
			in->nextFrameAddrBuf, addressToRender);

		/* use addressToRender to send out message. */
		vfe_send_output_msg(in->whichOutputPath,
				addressToRender[0], addressToRender[1]);

	} else {
		/* ackPending is still there, accumulate dropped frame count.
		 * These count can be read through ioctrl command. */
		CDBG("waiting frame ACK\n");

		if (in->whichOutputPath == 0)
			ctrl->vfeDroppedFrameCounts.output1Count++;

		if (in->whichOutputPath == 1)
			ctrl->vfeDroppedFrameCounts.output2Count++;
	}

	/* in case of multishot when upper layer did not ack, there will still
	 * be a snapshot done msg sent out, even though the number of frames
	 * sent out may be less than the desired number of frames.  snapshot
	 * done msg would be helpful to indicate that vfe pipeline has stop,
	 * and in good known state.
	 */
	if (ctrl->vfeOperationMode)
		in->snapshotPendingCount--;
}