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
struct veth_lpar_connection {int dummy; } ;
typedef  int /*<<< orphan*/  HvLpEvent_Rc ;

/* Variables and functions */
 int /*<<< orphan*/  HvLpEvent_AckInd_NoAck ; 
 int /*<<< orphan*/  HvLpEvent_AckType_ImmediateAck ; 
 int /*<<< orphan*/  veth_signalevent (struct veth_lpar_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline HvLpEvent_Rc veth_signaldata(struct veth_lpar_connection *cnx,
					   u16 subtype, u64 token, void *data)
{
	u64 *p = (u64 *) data;

	return veth_signalevent(cnx, subtype, HvLpEvent_AckInd_NoAck,
				HvLpEvent_AckType_ImmediateAck,
				token, p[0], p[1], p[2], p[3], p[4]);
}