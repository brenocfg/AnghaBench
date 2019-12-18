#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  seg_num; } ;
struct ib_rmpp_mad {TYPE_1__ rmpp_hdr; } ;
struct ib_mad_recv_buf {scalar_t__ mad; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int get_seg_num(struct ib_mad_recv_buf *seg)
{
	struct ib_rmpp_mad *rmpp_mad;

	rmpp_mad = (struct ib_rmpp_mad *) seg->mad;
	return be32_to_cpu(rmpp_mad->rmpp_hdr.seg_num);
}