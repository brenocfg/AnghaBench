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
typedef  void const tlv_desc ;
struct tipc_name_table_query {int /*<<< orphan*/  upbound; int /*<<< orphan*/  lowbound; int /*<<< orphan*/  type; int /*<<< orphan*/  depth; } ;
struct sk_buff {scalar_t__ data; } ;
struct print_buf {int dummy; } ;

/* Variables and functions */
 int MAX_NAME_TBL_QUERY ; 
 int /*<<< orphan*/  TIPC_CFG_TLV_ERROR ; 
 int /*<<< orphan*/  TIPC_TLV_NAME_TBL_QUERY ; 
 int /*<<< orphan*/  TIPC_TLV_ULTRA_STRING ; 
 int /*<<< orphan*/  TLV_CHECK (void const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TLV_DATA (void const*) ; 
 int /*<<< orphan*/  TLV_SET (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TLV_SPACE (int) ; 
 int /*<<< orphan*/  nametbl_list (struct print_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cfg_reply_alloc (int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cfg_reply_error_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_nametbl_lock ; 
 int /*<<< orphan*/  tipc_printbuf_init (struct print_buf*,scalar_t__,int) ; 
 int tipc_printbuf_validate (struct print_buf*) ; 

struct sk_buff *tipc_nametbl_get(const void *req_tlv_area, int req_tlv_space)
{
	struct sk_buff *buf;
	struct tipc_name_table_query *argv;
	struct tlv_desc *rep_tlv;
	struct print_buf b;
	int str_len;

	if (!TLV_CHECK(req_tlv_area, req_tlv_space, TIPC_TLV_NAME_TBL_QUERY))
		return tipc_cfg_reply_error_string(TIPC_CFG_TLV_ERROR);

	buf = tipc_cfg_reply_alloc(TLV_SPACE(MAX_NAME_TBL_QUERY));
	if (!buf)
		return NULL;

	rep_tlv = (struct tlv_desc *)buf->data;
	tipc_printbuf_init(&b, TLV_DATA(rep_tlv), MAX_NAME_TBL_QUERY);
	argv = (struct tipc_name_table_query *)TLV_DATA(req_tlv_area);
	read_lock_bh(&tipc_nametbl_lock);
	nametbl_list(&b, ntohl(argv->depth), ntohl(argv->type),
		     ntohl(argv->lowbound), ntohl(argv->upbound));
	read_unlock_bh(&tipc_nametbl_lock);
	str_len = tipc_printbuf_validate(&b);

	skb_put(buf, TLV_SPACE(str_len));
	TLV_SET(rep_tlv, TIPC_TLV_ULTRA_STRING, NULL, str_len);

	return buf;
}