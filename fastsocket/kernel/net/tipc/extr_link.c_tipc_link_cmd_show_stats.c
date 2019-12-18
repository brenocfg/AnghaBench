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
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 int MAX_LINK_STATS_INFO ; 
 char* TIPC_CFG_TLV_ERROR ; 
 int /*<<< orphan*/  TIPC_TLV_LINK_NAME ; 
 int /*<<< orphan*/  TIPC_TLV_ULTRA_STRING ; 
 int /*<<< orphan*/  TLV_CHECK (void const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ TLV_DATA (void const*) ; 
 int /*<<< orphan*/  TLV_SET (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TLV_SPACE (int) ; 
 int /*<<< orphan*/  buf_discard (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cfg_reply_alloc (int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cfg_reply_error_string (char*) ; 
 int tipc_link_stats (char*,char*,int) ; 

struct sk_buff *tipc_link_cmd_show_stats(const void *req_tlv_area, int req_tlv_space)
{
	struct sk_buff *buf;
	struct tlv_desc *rep_tlv;
	int str_len;

	if (!TLV_CHECK(req_tlv_area, req_tlv_space, TIPC_TLV_LINK_NAME))
		return tipc_cfg_reply_error_string(TIPC_CFG_TLV_ERROR);

	buf = tipc_cfg_reply_alloc(TLV_SPACE(MAX_LINK_STATS_INFO));
	if (!buf)
		return NULL;

	rep_tlv = (struct tlv_desc *)buf->data;

	str_len = tipc_link_stats((char *)TLV_DATA(req_tlv_area),
				  (char *)TLV_DATA(rep_tlv), MAX_LINK_STATS_INFO);
	if (!str_len) {
		buf_discard(buf);
		return tipc_cfg_reply_error_string("link not found");
	}

	skb_put(buf, TLV_SPACE(str_len));
	TLV_SET(rep_tlv, TIPC_TLV_ULTRA_STRING, NULL, str_len);

	return buf;
}