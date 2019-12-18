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
struct ipw_priv {int dummy; } ;
struct host_cmd {void* param; int /*<<< orphan*/  len; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int __ipw_send_cmd (struct ipw_priv*,struct host_cmd*) ; 

__attribute__((used)) static int ipw_send_cmd_pdu(struct ipw_priv *priv, u8 command, u8 len,
			    void *data)
{
	struct host_cmd cmd = {
		.cmd = command,
		.len = len,
		.param = data,
	};

	return __ipw_send_cmd(priv, &cmd);
}