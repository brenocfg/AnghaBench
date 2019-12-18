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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct veth_lpar_connection {int /*<<< orphan*/  dst_inst; int /*<<< orphan*/  src_inst; int /*<<< orphan*/  remote_lp; } ;
typedef  int /*<<< orphan*/  HvLpEvent_Rc ;
typedef  int /*<<< orphan*/  HvLpEvent_AckType ;
typedef  int /*<<< orphan*/  HvLpEvent_AckInd ;

/* Variables and functions */
 int /*<<< orphan*/  HvCallEvent_signalLpEventFast (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HvLpEvent_Type_VirtualLan ; 

__attribute__((used)) static inline HvLpEvent_Rc
veth_signalevent(struct veth_lpar_connection *cnx, u16 subtype,
		 HvLpEvent_AckInd ackind, HvLpEvent_AckType acktype,
		 u64 token,
		 u64 data1, u64 data2, u64 data3, u64 data4, u64 data5)
{
	return HvCallEvent_signalLpEventFast(cnx->remote_lp,
					     HvLpEvent_Type_VirtualLan,
					     subtype, ackind, acktype,
					     cnx->src_inst,
					     cnx->dst_inst,
					     token, data1, data2, data3,
					     data4, data5);
}