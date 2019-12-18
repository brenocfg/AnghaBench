#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int reserved1; int reserved2; int reserved3; int reserved4; int reserved5; int /*<<< orphan*/  status_fifo_lo; int /*<<< orphan*/  status_fifo_hi; int /*<<< orphan*/  login_ID_misc; } ;
struct sbp2_lu {int /*<<< orphan*/  management_agent_addr; int /*<<< orphan*/  ne; TYPE_3__ logout_orb_dma; TYPE_3__* logout_orb; int /*<<< orphan*/  status_fifo_addr; TYPE_1__* login_response; struct sbp2_fwhost_info* hi; } ;
struct sbp2_logout_orb {int dummy; } ;
struct sbp2_fwhost_info {TYPE_2__* host; } ;
typedef  TYPE_3__ quadlet_t ;
struct TYPE_8__ {int /*<<< orphan*/  node_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  length_login_ID; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  ORB_SET_FUNCTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORB_SET_LOGIN_ID (int /*<<< orphan*/ ) ; 
 TYPE_3__ ORB_SET_NODE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORB_SET_NOTIFY (int) ; 
 int /*<<< orphan*/  ORB_SET_STATUS_FIFO_HI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ORB_SET_STATUS_FIFO_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBP2_INFO (char*) ; 
 int /*<<< orphan*/  SBP2_LOGOUT_REQUEST ; 
 int hpsb_node_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 scalar_t__ sbp2util_access_timeout (struct sbp2_lu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp2util_cpu_to_be32_buffer (TYPE_3__*,int) ; 

__attribute__((used)) static int sbp2_logout_device(struct sbp2_lu *lu)
{
	struct sbp2_fwhost_info *hi = lu->hi;
	quadlet_t data[2];
	int error;

	lu->logout_orb->reserved1 = 0x0;
	lu->logout_orb->reserved2 = 0x0;
	lu->logout_orb->reserved3 = 0x0;
	lu->logout_orb->reserved4 = 0x0;

	lu->logout_orb->login_ID_misc = ORB_SET_FUNCTION(SBP2_LOGOUT_REQUEST);
	lu->logout_orb->login_ID_misc |=
			ORB_SET_LOGIN_ID(lu->login_response->length_login_ID);
	lu->logout_orb->login_ID_misc |= ORB_SET_NOTIFY(1);

	lu->logout_orb->reserved5 = 0x0;
	lu->logout_orb->status_fifo_hi =
		ORB_SET_STATUS_FIFO_HI(lu->status_fifo_addr, hi->host->node_id);
	lu->logout_orb->status_fifo_lo =
		ORB_SET_STATUS_FIFO_LO(lu->status_fifo_addr);

	sbp2util_cpu_to_be32_buffer(lu->logout_orb,
				    sizeof(struct sbp2_logout_orb));

	data[0] = ORB_SET_NODE_ID(hi->host->node_id);
	data[1] = lu->logout_orb_dma;
	sbp2util_cpu_to_be32_buffer(data, 8);

	error = hpsb_node_write(lu->ne, lu->management_agent_addr, data, 8);
	if (error)
		return error;

	/* wait up to 1 second for the device to complete logout */
	if (sbp2util_access_timeout(lu, HZ))
		return -EIO;

	SBP2_INFO("Logged out of SBP-2 device");
	return 0;
}