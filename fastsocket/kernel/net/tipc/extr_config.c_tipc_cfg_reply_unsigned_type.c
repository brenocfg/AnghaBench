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
typedef  int /*<<< orphan*/  value_net ;
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  TLV_SPACE (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_cfg_append_tlv (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* tipc_cfg_reply_alloc (int /*<<< orphan*/ ) ; 

struct sk_buff *tipc_cfg_reply_unsigned_type(u16 tlv_type, u32 value)
{
	struct sk_buff *buf;
	__be32 value_net;

	buf = tipc_cfg_reply_alloc(TLV_SPACE(sizeof(value)));
	if (buf) {
		value_net = htonl(value);
		tipc_cfg_append_tlv(buf, tlv_type, &value_net,
				    sizeof(value_net));
	}
	return buf;
}