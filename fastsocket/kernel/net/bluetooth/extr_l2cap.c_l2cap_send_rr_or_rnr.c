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
typedef  int /*<<< orphan*/  u16 ;
struct l2cap_pinfo {int conn_state; } ;

/* Variables and functions */
 int L2CAP_CONN_LOCAL_BUSY ; 
 int /*<<< orphan*/  L2CAP_SUPER_RCV_NOT_READY ; 
 int /*<<< orphan*/  L2CAP_SUPER_RCV_READY ; 
 int l2cap_send_sframe (struct l2cap_pinfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int l2cap_send_rr_or_rnr(struct l2cap_pinfo *pi, u16 control)
{
	if (pi->conn_state & L2CAP_CONN_LOCAL_BUSY)
		control |= L2CAP_SUPER_RCV_NOT_READY;
	else
		control |= L2CAP_SUPER_RCV_READY;

	return l2cap_send_sframe(pi, control);
}