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
typedef  int /*<<< orphan*/  unchar ;
typedef  int u32 ;
struct tipc_portid {int /*<<< orphan*/  node; } ;
struct tipc_name_seq {int dummy; } ;
struct tipc_cfg_msg_hdr {int /*<<< orphan*/  tcm_flags; int /*<<< orphan*/  tcm_len; int /*<<< orphan*/  tcm_type; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ BUF_HEADROOM ; 
 scalar_t__ MAX_H_SIZE ; 
 int TCM_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCM_F_REQUEST ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct tipc_cfg_msg_hdr*,struct tipc_cfg_msg_hdr*,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 struct sk_buff* tipc_cfg_do_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__) ; 
 int /*<<< orphan*/  tipc_send_buf2port (int,struct tipc_portid const*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void cfg_named_msg_event(void *userdata,
				u32 port_ref,
				struct sk_buff **buf,
				const unchar *msg,
				u32 size,
				u32 importance,
				struct tipc_portid const *orig,
				struct tipc_name_seq const *dest)
{
	struct tipc_cfg_msg_hdr *req_hdr;
	struct tipc_cfg_msg_hdr *rep_hdr;
	struct sk_buff *rep_buf;

	/* Validate configuration message header (ignore invalid message) */

	req_hdr = (struct tipc_cfg_msg_hdr *)msg;
	if ((size < sizeof(*req_hdr)) ||
	    (size != TCM_ALIGN(ntohl(req_hdr->tcm_len))) ||
	    (ntohs(req_hdr->tcm_flags) != TCM_F_REQUEST)) {
		warn("Invalid configuration message discarded\n");
		return;
	}

	/* Generate reply for request (if can't, return request) */

	rep_buf = tipc_cfg_do_cmd(orig->node,
				  ntohs(req_hdr->tcm_type),
				  msg + sizeof(*req_hdr),
				  size - sizeof(*req_hdr),
				  BUF_HEADROOM + MAX_H_SIZE + sizeof(*rep_hdr));
	if (rep_buf) {
		skb_push(rep_buf, sizeof(*rep_hdr));
		rep_hdr = (struct tipc_cfg_msg_hdr *)rep_buf->data;
		memcpy(rep_hdr, req_hdr, sizeof(*rep_hdr));
		rep_hdr->tcm_len = htonl(rep_buf->len);
		rep_hdr->tcm_flags &= htons(~TCM_F_REQUEST);
	} else {
		rep_buf = *buf;
		*buf = NULL;
	}

	/* NEED TO ADD CODE TO HANDLE FAILED SEND (SUCH AS CONGESTION) */
	tipc_send_buf2port(port_ref, orig, rep_buf, rep_buf->len);
}