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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TLV_SPACE (int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tipc_cfg_append_tlv (struct sk_buff*,int /*<<< orphan*/ ,char*,int) ; 
 struct sk_buff* tipc_cfg_reply_alloc (int /*<<< orphan*/ ) ; 

struct sk_buff *tipc_cfg_reply_string_type(u16 tlv_type, char *string)
{
	struct sk_buff *buf;
	int string_len = strlen(string) + 1;

	buf = tipc_cfg_reply_alloc(TLV_SPACE(string_len));
	if (buf)
		tipc_cfg_append_tlv(buf, tlv_type, string, string_len);
	return buf;
}