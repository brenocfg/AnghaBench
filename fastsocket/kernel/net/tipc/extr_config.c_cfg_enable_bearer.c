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
struct tipc_bearer_config {int /*<<< orphan*/  priority; int /*<<< orphan*/  detect_scope; int /*<<< orphan*/  name; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 char* TIPC_CFG_TLV_ERROR ; 
 int /*<<< orphan*/  TIPC_TLV_BEARER_CONFIG ; 
 int /*<<< orphan*/  TLV_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TLV_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_tlv_area ; 
 int /*<<< orphan*/  req_tlv_space ; 
 struct sk_buff* tipc_cfg_reply_error_string (char*) ; 
 struct sk_buff* tipc_cfg_reply_none () ; 
 scalar_t__ tipc_enable_bearer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *cfg_enable_bearer(void)
{
	struct tipc_bearer_config *args;

	if (!TLV_CHECK(req_tlv_area, req_tlv_space, TIPC_TLV_BEARER_CONFIG))
		return tipc_cfg_reply_error_string(TIPC_CFG_TLV_ERROR);

	args = (struct tipc_bearer_config *)TLV_DATA(req_tlv_area);
	if (tipc_enable_bearer(args->name,
			       ntohl(args->detect_scope),
			       ntohl(args->priority)))
		return tipc_cfg_reply_error_string("unable to enable bearer");

	return tipc_cfg_reply_none();
}