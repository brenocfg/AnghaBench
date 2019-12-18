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
struct bnx2i_endpoint {int state; TYPE_1__* hba; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnic_dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
#define  EP_STATE_CLEANUP_FAILED 140 
#define  EP_STATE_CONNECT_COMPL 139 
#define  EP_STATE_CONNECT_FAILED 138 
#define  EP_STATE_CONNECT_START 137 
#define  EP_STATE_DISCONN_TIMEDOUT 136 
#define  EP_STATE_LOGOUT_RESP_RCVD 135 
#define  EP_STATE_LOGOUT_SENT 134 
#define  EP_STATE_OFLD_FAILED 133 
#define  EP_STATE_TCP_FIN_RCVD 132 
#define  EP_STATE_TCP_RST_RCVD 131 
#define  EP_STATE_ULP_UPDATE_COMPL 130 
#define  EP_STATE_ULP_UPDATE_FAILED 129 
#define  EP_STATE_ULP_UPDATE_START 128 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_ep_tcp_conn_active(struct bnx2i_endpoint *bnx2i_ep)
{
	int ret;
	int cnic_dev_10g = 0;

	if (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_ep->hba->cnic_dev_type))
		cnic_dev_10g = 1;

	switch (bnx2i_ep->state) {
	case EP_STATE_CLEANUP_FAILED:
	case EP_STATE_OFLD_FAILED:
	case EP_STATE_DISCONN_TIMEDOUT:
		ret = 0;
		break;
	case EP_STATE_CONNECT_START:
	case EP_STATE_CONNECT_FAILED:
	case EP_STATE_CONNECT_COMPL:
	case EP_STATE_ULP_UPDATE_START:
	case EP_STATE_ULP_UPDATE_COMPL:
	case EP_STATE_TCP_FIN_RCVD:
	case EP_STATE_LOGOUT_SENT:
	case EP_STATE_LOGOUT_RESP_RCVD:
	case EP_STATE_ULP_UPDATE_FAILED:
		ret = 1;
		break;
	case EP_STATE_TCP_RST_RCVD:
		if (cnic_dev_10g)
			ret = 0;
		else
			ret = 1;
		break;
	default:
		ret = 0;
	}

	return ret;
}