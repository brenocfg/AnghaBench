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
typedef  scalar_t__ u16 ;
struct sock {int dummy; } ;
struct l2cap_pinfo {unsigned long omtu; unsigned long flush_to; int conf_state; int mode; int dcid; void* max_pdu_size; int /*<<< orphan*/  monitor_timeout; int /*<<< orphan*/  retrans_timeout; int /*<<< orphan*/  remote_tx_win; int /*<<< orphan*/  fcs; } ;
struct l2cap_conf_rfc {int mode; int /*<<< orphan*/  max_pdu_size; int /*<<< orphan*/  monitor_timeout; int /*<<< orphan*/  retrans_timeout; int /*<<< orphan*/  txwin_size; } ;
struct l2cap_conf_req {void* flags; void* dcid; void* data; } ;
typedef  int /*<<< orphan*/  rfc ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,void*,int,void*) ; 
 int ECONNREFUSED ; 
#define  L2CAP_CONF_FLUSH_TO 132 
#define  L2CAP_CONF_MTU 131 
 int L2CAP_CONF_OPT_SIZE ; 
#define  L2CAP_CONF_RFC 130 
 int L2CAP_CONF_STATE2_DEVICE ; 
 scalar_t__ L2CAP_CONF_SUCCESS ; 
 scalar_t__ L2CAP_CONF_UNACCEPT ; 
 unsigned long L2CAP_DEFAULT_MIN_MTU ; 
#define  L2CAP_MODE_ERTM 129 
#define  L2CAP_MODE_STREAMING 128 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  l2cap_add_conf_opt (void**,int const,int,unsigned long) ; 
 scalar_t__ l2cap_get_conf_opt (void**,int*,int*,unsigned long*) ; 
 struct l2cap_pinfo* l2cap_pi (struct sock*) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct l2cap_conf_rfc*,void*,int) ; 

__attribute__((used)) static int l2cap_parse_conf_rsp(struct sock *sk, void *rsp, int len, void *data, u16 *result)
{
	struct l2cap_pinfo *pi = l2cap_pi(sk);
	struct l2cap_conf_req *req = data;
	void *ptr = req->data;
	int type, olen;
	unsigned long val;
	struct l2cap_conf_rfc rfc;

	BT_DBG("sk %p, rsp %p, len %d, req %p", sk, rsp, len, data);

	while (len >= L2CAP_CONF_OPT_SIZE) {
		len -= l2cap_get_conf_opt(&rsp, &type, &olen, &val);

		switch (type) {
		case L2CAP_CONF_MTU:
			if (val < L2CAP_DEFAULT_MIN_MTU) {
				*result = L2CAP_CONF_UNACCEPT;
				pi->omtu = L2CAP_DEFAULT_MIN_MTU;
			} else
				pi->omtu = val;
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_MTU, 2, pi->omtu);
			break;

		case L2CAP_CONF_FLUSH_TO:
			pi->flush_to = val;
			l2cap_add_conf_opt(&ptr, L2CAP_CONF_FLUSH_TO,
							2, pi->flush_to);
			break;

		case L2CAP_CONF_RFC:
			if (olen == sizeof(rfc))
				memcpy(&rfc, (void *)val, olen);

			if ((pi->conf_state & L2CAP_CONF_STATE2_DEVICE) &&
							rfc.mode != pi->mode)
				return -ECONNREFUSED;

			pi->mode = rfc.mode;
			pi->fcs = 0;

			l2cap_add_conf_opt(&ptr, L2CAP_CONF_RFC,
					sizeof(rfc), (unsigned long) &rfc);
			break;
		}
	}

	if (*result == L2CAP_CONF_SUCCESS) {
		switch (rfc.mode) {
		case L2CAP_MODE_ERTM:
			pi->remote_tx_win   = rfc.txwin_size;
			pi->retrans_timeout = rfc.retrans_timeout;
			pi->monitor_timeout = rfc.monitor_timeout;
			pi->max_pdu_size    = le16_to_cpu(rfc.max_pdu_size);
			break;
		case L2CAP_MODE_STREAMING:
			pi->max_pdu_size    = le16_to_cpu(rfc.max_pdu_size);
			break;
		}
	}

	req->dcid   = cpu_to_le16(pi->dcid);
	req->flags  = cpu_to_le16(0x0000);

	return ptr - data;
}