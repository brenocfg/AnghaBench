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
typedef  int /*<<< orphan*/  u8 ;
struct ipw_retry_limit {int /*<<< orphan*/  long_retry_limit; int /*<<< orphan*/  short_retry_limit; } ;
struct ipw_priv {int dummy; } ;
typedef  int /*<<< orphan*/  retry_limit ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_CMD_RETRY_LIMIT ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int ipw_send_cmd_pdu (struct ipw_priv*,int /*<<< orphan*/ ,int,struct ipw_retry_limit*) ; 

__attribute__((used)) static int ipw_send_retry_limit(struct ipw_priv *priv, u8 slimit, u8 llimit)
{
	struct ipw_retry_limit retry_limit = {
		.short_retry_limit = slimit,
		.long_retry_limit = llimit
	};

	if (!priv) {
		IPW_ERROR("Invalid args\n");
		return -1;
	}

	return ipw_send_cmd_pdu(priv, IPW_CMD_RETRY_LIMIT, sizeof(retry_limit),
				&retry_limit);
}