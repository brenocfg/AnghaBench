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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  TIPC_CFG_TLV_ERROR ; 
 int /*<<< orphan*/  TIPC_TLV_UNSIGNED ; 
 int /*<<< orphan*/  TLV_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLV_DATA (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_tlv_area ; 
 int /*<<< orphan*/  req_tlv_space ; 
 struct sk_buff* tipc_cfg_reply_error_string (int /*<<< orphan*/ ) ; 
 struct sk_buff* tipc_cfg_reply_none () ; 
 int tipc_remote_management ; 

__attribute__((used)) static struct sk_buff *cfg_set_remote_mng(void)
{
	u32 value;

	if (!TLV_CHECK(req_tlv_area, req_tlv_space, TIPC_TLV_UNSIGNED))
		return tipc_cfg_reply_error_string(TIPC_CFG_TLV_ERROR);

	value = ntohl(*(__be32 *)TLV_DATA(req_tlv_area));
	tipc_remote_management = (value != 0);
	return tipc_cfg_reply_none();
}