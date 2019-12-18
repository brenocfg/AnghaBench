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
typedef  int u32 ;
struct TYPE_4__ {void* paylen_newwin; int /*<<< orphan*/  rmpp_rtime_flags; void* seg_num; } ;
struct ib_rmpp_mad {TYPE_2__ rmpp_hdr; } ;
struct TYPE_3__ {int seg_count; int timeout_ms; struct ib_rmpp_mad* mad; } ;
struct ib_mad_send_wr_private {int seg_num; int pad; int /*<<< orphan*/  timeout; TYPE_1__ send_buf; } ;

/* Variables and functions */
 int IB_MGMT_RMPP_DATA ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_FLAG_ACTIVE ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_FLAG_FIRST ; 
 int /*<<< orphan*/  IB_MGMT_RMPP_FLAG_LAST ; 
 void* cpu_to_be32 (int) ; 
 int ib_send_mad (struct ib_mad_send_wr_private*) ; 
 int /*<<< orphan*/  ib_set_rmpp_flags (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 

__attribute__((used)) static int send_next_seg(struct ib_mad_send_wr_private *mad_send_wr)
{
	struct ib_rmpp_mad *rmpp_mad;
	int timeout;
	u32 paylen = 0;

	rmpp_mad = mad_send_wr->send_buf.mad;
	ib_set_rmpp_flags(&rmpp_mad->rmpp_hdr, IB_MGMT_RMPP_FLAG_ACTIVE);
	rmpp_mad->rmpp_hdr.seg_num = cpu_to_be32(++mad_send_wr->seg_num);

	if (mad_send_wr->seg_num == 1) {
		rmpp_mad->rmpp_hdr.rmpp_rtime_flags |= IB_MGMT_RMPP_FLAG_FIRST;
		paylen = mad_send_wr->send_buf.seg_count * IB_MGMT_RMPP_DATA -
			 mad_send_wr->pad;
	}

	if (mad_send_wr->seg_num == mad_send_wr->send_buf.seg_count) {
		rmpp_mad->rmpp_hdr.rmpp_rtime_flags |= IB_MGMT_RMPP_FLAG_LAST;
		paylen = IB_MGMT_RMPP_DATA - mad_send_wr->pad;
	}
	rmpp_mad->rmpp_hdr.paylen_newwin = cpu_to_be32(paylen);

	/* 2 seconds for an ACK until we can find the packet lifetime */
	timeout = mad_send_wr->send_buf.timeout_ms;
	if (!timeout || timeout > 2000)
		mad_send_wr->timeout = msecs_to_jiffies(2000);

	return ib_send_mad(mad_send_wr);
}