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
struct l2cap_cmd_rej {int /*<<< orphan*/  reason; } ;
typedef  struct l2cap_cmd_rej u8 ;
typedef  int u16 ;
struct sk_buff {int len; struct l2cap_cmd_rej* data; } ;
struct l2cap_conn {int dummy; } ;
struct l2cap_cmd_hdr {int code; int /*<<< orphan*/  ident; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  rej ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int EINVAL ; 
 int L2CAP_CMD_HDR_SIZE ; 
#define  L2CAP_COMMAND_REJ 138 
#define  L2CAP_CONF_REQ 137 
#define  L2CAP_CONF_RSP 136 
#define  L2CAP_CONN_REQ 135 
#define  L2CAP_CONN_RSP 134 
#define  L2CAP_DISCONN_REQ 133 
#define  L2CAP_DISCONN_RSP 132 
#define  L2CAP_ECHO_REQ 131 
#define  L2CAP_ECHO_RSP 130 
#define  L2CAP_INFO_REQ 129 
#define  L2CAP_INFO_RSP 128 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_command_rej (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int l2cap_config_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,int,struct l2cap_cmd_rej*) ; 
 int l2cap_config_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int l2cap_connect_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int l2cap_connect_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int l2cap_disconnect_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int l2cap_disconnect_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int l2cap_information_req (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int l2cap_information_rsp (struct l2cap_conn*,struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*) ; 
 int /*<<< orphan*/  l2cap_raw_recv (struct l2cap_conn*,struct sk_buff*) ; 
 int /*<<< orphan*/  l2cap_send_cmd (struct l2cap_conn*,int /*<<< orphan*/ ,int const,int,struct l2cap_cmd_rej*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct l2cap_cmd_hdr*,struct l2cap_cmd_rej*,int) ; 

__attribute__((used)) static inline void l2cap_sig_channel(struct l2cap_conn *conn, struct sk_buff *skb)
{
	u8 *data = skb->data;
	int len = skb->len;
	struct l2cap_cmd_hdr cmd;
	int err = 0;

	l2cap_raw_recv(conn, skb);

	while (len >= L2CAP_CMD_HDR_SIZE) {
		u16 cmd_len;
		memcpy(&cmd, data, L2CAP_CMD_HDR_SIZE);
		data += L2CAP_CMD_HDR_SIZE;
		len  -= L2CAP_CMD_HDR_SIZE;

		cmd_len = le16_to_cpu(cmd.len);

		BT_DBG("code 0x%2.2x len %d id 0x%2.2x", cmd.code, cmd_len, cmd.ident);

		if (cmd_len > len || !cmd.ident) {
			BT_DBG("corrupted command");
			break;
		}

		switch (cmd.code) {
		case L2CAP_COMMAND_REJ:
			l2cap_command_rej(conn, &cmd, data);
			break;

		case L2CAP_CONN_REQ:
			err = l2cap_connect_req(conn, &cmd, data);
			break;

		case L2CAP_CONN_RSP:
			err = l2cap_connect_rsp(conn, &cmd, data);
			break;

		case L2CAP_CONF_REQ:
			err = l2cap_config_req(conn, &cmd, cmd_len, data);
			break;

		case L2CAP_CONF_RSP:
			err = l2cap_config_rsp(conn, &cmd, data);
			break;

		case L2CAP_DISCONN_REQ:
			err = l2cap_disconnect_req(conn, &cmd, data);
			break;

		case L2CAP_DISCONN_RSP:
			err = l2cap_disconnect_rsp(conn, &cmd, data);
			break;

		case L2CAP_ECHO_REQ:
			l2cap_send_cmd(conn, cmd.ident, L2CAP_ECHO_RSP, cmd_len, data);
			break;

		case L2CAP_ECHO_RSP:
			break;

		case L2CAP_INFO_REQ:
			err = l2cap_information_req(conn, &cmd, data);
			break;

		case L2CAP_INFO_RSP:
			err = l2cap_information_rsp(conn, &cmd, data);
			break;

		default:
			BT_ERR("Unknown signaling command 0x%2.2x", cmd.code);
			err = -EINVAL;
			break;
		}

		if (err) {
			struct l2cap_cmd_rej rej;
			BT_DBG("error %d", err);

			/* FIXME: Map err to a valid reason */
			rej.reason = cpu_to_le16(0);
			l2cap_send_cmd(conn, cmd.ident, L2CAP_COMMAND_REJ, sizeof(rej), &rej);
		}

		data += cmd_len;
		len  -= cmd_len;
	}

	kfree_skb(skb);
}