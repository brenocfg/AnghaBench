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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 char* TIPC_CFG_TLV_ERROR ; 
 int /*<<< orphan*/  TIPC_TLV_BEARER_NAME ; 
 int /*<<< orphan*/  TLV_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLV_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_tlv_area ; 
 int /*<<< orphan*/  req_tlv_space ; 
 struct sk_buff* tipc_cfg_reply_error_string (char*) ; 
 struct sk_buff* tipc_cfg_reply_none () ; 
 scalar_t__ tipc_disable_bearer (char*) ; 

__attribute__((used)) static struct sk_buff *cfg_disable_bearer(void)
{
	if (!TLV_CHECK(req_tlv_area, req_tlv_space, TIPC_TLV_BEARER_NAME))
		return tipc_cfg_reply_error_string(TIPC_CFG_TLV_ERROR);

	if (tipc_disable_bearer((char *)TLV_DATA(req_tlv_area)))
		return tipc_cfg_reply_error_string("unable to disable bearer");

	return tipc_cfg_reply_none();
}