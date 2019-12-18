#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct rxrpc_call {TYPE_2__* conn; } ;
struct TYPE_4__ {TYPE_1__* security; } ;
struct TYPE_3__ {int (* verify_packet ) (struct rxrpc_call const*,struct sk_buff*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct rxrpc_call const*,struct sk_buff*,int /*<<< orphan*/ *) ; 

int rxrpc_verify_packet(const struct rxrpc_call *call, struct sk_buff *skb,
			u32 *_abort_code)
{
	if (call->conn->security)
		return call->conn->security->verify_packet(
			call, skb, _abort_code);
	return 0;
}