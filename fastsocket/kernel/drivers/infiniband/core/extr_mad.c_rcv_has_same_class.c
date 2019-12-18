#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ mad; } ;
struct ib_mad_send_wr_private {TYPE_2__ send_buf; } ;
struct TYPE_10__ {TYPE_4__* mad; } ;
struct ib_mad_recv_wc {TYPE_5__ recv_buf; } ;
struct TYPE_6__ {scalar_t__ mgmt_class; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct TYPE_8__ {scalar_t__ mgmt_class; } ;
struct TYPE_9__ {TYPE_3__ mad_hdr; } ;

/* Variables and functions */

__attribute__((used)) static inline int rcv_has_same_class(struct ib_mad_send_wr_private *wr,
				     struct ib_mad_recv_wc *rwc)
{
	return ((struct ib_mad *)(wr->send_buf.mad))->mad_hdr.mgmt_class ==
		rwc->recv_buf.mad->mad_hdr.mgmt_class;
}