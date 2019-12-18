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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;
struct l2cap_pinfo {int conf_len; unsigned long flush_to; int num_conf_rsp; int mode; unsigned long omtu; unsigned long fcs; int dcid; int /*<<< orphan*/  conf_state; int /*<<< orphan*/  max_pdu_size; int /*<<< orphan*/  remote_tx_win; int /*<<< orphan*/  remote_max_tx; TYPE_1__* conn; scalar_t__ num_conf_req; void* conf_req; } ;
struct l2cap_conf_rsp {void* flags; void* result; void* scid; void* data; } ;
struct l2cap_conf_rfc {int mode; int /*<<< orphan*/  max_pdu_size; int /*<<< orphan*/  txwin_size; int /*<<< orphan*/  monitor_timeout; int /*<<< orphan*/  retrans_timeout; int /*<<< orphan*/  max_transmit; } ;
typedef  int /*<<< orphan*/  rfc ;
struct TYPE_2__ {int /*<<< orphan*/  feat_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*) ; 
 int ECONNREFUSED ; 
#define  L2CAP_CONF_FCS 135 
#define  L2CAP_CONF_FLUSH_TO 134 
 int L2CAP_CONF_HINT ; 
 int L2CAP_CONF_MASK ; 
 int /*<<< orphan*/  L2CAP_CONF_MODE_DONE ; 
#define  L2CAP_CONF_MTU 133 
 int /*<<< orphan*/  L2CAP_CONF_MTU_DONE ; 
 int /*<<< orphan*/  L2CAP_CONF_NO_FCS_RECV ; 
 int L2CAP_CONF_OPT_SIZE ; 
 int /*<<< orphan*/  L2CAP_CONF_OUTPUT_DONE ; 
#define  L2CAP_CONF_QOS 132 
#define  L2CAP_CONF_RFC 131 
 int /*<<< orphan*/  L2CAP_CONF_STATE2_DEVICE ; 
 scalar_t__ L2CAP_CONF_SUCCESS ; 
 scalar_t__ L2CAP_CONF_UNACCEPT ; 
 scalar_t__ L2CAP_CONF_UNKNOWN ; 
 scalar_t__ L2CAP_DEFAULT_MIN_MTU ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_MONITOR_TO ; 
 scalar_t__ L2CAP_DEFAULT_MTU ; 
 int /*<<< orphan*/  L2CAP_DEFAULT_RETRANS_TO ; 
 unsigned long L2CAP_FCS_NONE ; 
#define  L2CAP_MODE_BASIC 130 
#define  L2CAP_MODE_ERTM 129 
#define  L2CAP_MODE_STREAMING 128 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  l2cap_add_conf_opt (void**,int const,int,unsigned long) ; 
 scalar_t__ l2cap_get_conf_opt (void**,int*,int*,unsigned long*) ; 
 int /*<<< orphan*/  l2cap_mode_supported (int,int /*<<< orphan*/ ) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 int l2cap_select_mode (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct l2cap_conf_rfc*,void*,int) ; 
 int /*<<< orphan*/  memset (struct l2cap_conf_rfc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int l2cap_parse_conf_req(struct sock *sk, void *data)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct l2cap_conf_rsp *rsp = data;
	void *ptr = rsp->data;
	void *req = pi->conf_req;
	int len = pi->conf_len;
	int type, hint, olen;
	unsigned long val;
	struct l2cap_conf_rfc rfc = { .mode = L2CAP_MODE_BASIC };
	u16 mtu = L2CAP_DEFAULT_MTU;
	u16 result = L2CAP_CONF_SUCCESS;

	BT_DBG("sk %p", sk);

	while (len >= L2CAP_CONF_OPT_SIZE) {
		len -= l2cap_get_conf_opt(&req, &type, &olen, &val);

		hint  = type & L2CAP_CONF_HINT;
		type &= L2CAP_CONF_MASK;

		switch (type) {
		case L2CAP_CONF_MTU:
			mtu = val;
			break;

		case L2CAP_CONF_FLUSH_TO:
			pi->flush_to = val;
			break;

		case L2CAP_CONF_QOS:
			break;

		case L2CAP_CONF_RFC:
			if (olen == sizeof(rfc))
				memcpy(&rfc, (void *) val, olen);
			break;

		case L2CAP_CONF_FCS:
			if (val == L2CAP_FCS_NONE)
				pi->conf_state |= L2CAP_CONF_NO_FCS_RECV;

			break;

		default:
			if (hint)
				break;

			result = L2CAP_CONF_UNKNOWN;
			*((u8 *) ptr++) = type;
			break;
		}
	}

	if (pi->num_conf_rsp || pi->num_conf_req)
		goto done;

	switch (pi->mode) {
	case L2CAP_MODE_STREAMING:
	case L2CAP_MODE_ERTM:
		pi->conf_state |= L2CAP_CONF_STATE2_DEVICE;
		if (!l2cap_mode_supported(pi->mode, pi->conn->feat_mask))
			return -ECONNREFUSED;
		break;
	default:
		pi->mode = l2cap_select_mode(rfc.mode, pi->conn->feat_mask);
		break;
	}

done:
	if (pi->mode != rfc.mode) {
		result = L2CAP_CONF_UNACCEPT;
		rfc.mode = pi->mode;

		if (pi->num_conf_rsp == 1)
			return -ECONNREFUSED;

		l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC,
					sizeof(rfc), (unsigned long) &rfc);
	}


	if (result == L2CAP_CONF_SUCCESS) {
		/* Configure output options and let the other side know
		 * which ones we don't like. */

		if (mtu < L2CAP_DEFAULT_MIN_MTU)
			result = L2CAP_CONF_UNACCEPT;
		else {
			pi->omtu = mtu;
			pi->conf_state |= L2CAP_CONF_MTU_DONE;
		}
		l2cap_add_conf_opt(&ptr, L2CAP_CONF_MTU, 2, pi->omtu);

		switch (rfc.mode) {
		case L2CAP_MODE_BASIC:
			pi->fcs = L2CAP_FCS_NONE;
			pi->conf_state |= L2CAP_CONF_MODE_DONE;
			break;

		case L2CAP_MODE_ERTM:
			pi->remote_tx_win = rfc.txwin_size;
			pi->remote_max_tx = rfc.max_transmit;
			pi->max_pdu_size = rfc.max_pdu_size;

			rfc.retrans_timeout = L2CAP_DEFAULT_RETRANS_TO;
			rfc.monitor_timeout = L2CAP_DEFAULT_MONITOR_TO;

			pi->conf_state |= L2CAP_CONF_MODE_DONE;

			l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC,
					sizeof(rfc), (unsigned long) &rfc);

			break;

		case L2CAP_MODE_STREAMING:
			pi->remote_tx_win = rfc.txwin_size;
			pi->max_pdu_size = rfc.max_pdu_size;

			pi->conf_state |= L2CAP_CONF_MODE_DONE;

			l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC,
					sizeof(rfc), (unsigned long) &rfc);

			break;

		default:
			result = L2CAP_CONF_UNACCEPT;

			memset(&rfc, 0, sizeof(rfc));
			rfc.mode = pi->mode;
		}

		if (result == L2CAP_CONF_SUCCESS)
			pi->conf_state |= L2CAP_CONF_OUTPUT_DONE;
	}
	rsp->scid   = cpu_to_le16(pi->dcid);
	rsp->result = cpu_to_le16(result);
	rsp->flags  = cpu_to_le16(0x0000);

	return ptr - data;
}