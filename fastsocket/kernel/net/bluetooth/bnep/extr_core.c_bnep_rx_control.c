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
typedef  int u8 ;
struct bnep_session {int dummy; } ;
typedef  int /*<<< orphan*/  pkt ;

/* Variables and functions */
#define  BNEP_CMD_NOT_UNDERSTOOD 134 
 int BNEP_CONTROL ; 
#define  BNEP_FILTER_MULTI_ADDR_RSP 133 
#define  BNEP_FILTER_MULTI_ADDR_SET 132 
#define  BNEP_FILTER_NET_TYPE_RSP 131 
#define  BNEP_FILTER_NET_TYPE_SET 130 
#define  BNEP_SETUP_CONN_REQ 129 
#define  BNEP_SETUP_CONN_RSP 128 
 int bnep_ctrl_set_mcfilter (struct bnep_session*,void*,int) ; 
 int bnep_ctrl_set_netfilter (struct bnep_session*,void*,int) ; 
 int /*<<< orphan*/  bnep_send (struct bnep_session*,int*,int) ; 

__attribute__((used)) static int bnep_rx_control(struct bnep_session *s, void *data, int len)
{
	u8  cmd = *(u8 *)data;
	int err = 0;

	data++; len--;

	switch (cmd) {
	case BNEP_CMD_NOT_UNDERSTOOD:
	case BNEP_SETUP_CONN_REQ:
	case BNEP_SETUP_CONN_RSP:
	case BNEP_FILTER_NET_TYPE_RSP:
	case BNEP_FILTER_MULTI_ADDR_RSP:
		/* Ignore these for now */
		break;

	case BNEP_FILTER_NET_TYPE_SET:
		err = bnep_ctrl_set_netfilter(s, data, len);
		break;

	case BNEP_FILTER_MULTI_ADDR_SET:
		err = bnep_ctrl_set_mcfilter(s, data, len);
		break;

	default: {
			u8 pkt[3];
			pkt[0] = BNEP_CONTROL;
			pkt[1] = BNEP_CMD_NOT_UNDERSTOOD;
			pkt[2] = cmd;
			bnep_send(s, pkt, sizeof(pkt));
		}
		break;
	}

	return err;
}