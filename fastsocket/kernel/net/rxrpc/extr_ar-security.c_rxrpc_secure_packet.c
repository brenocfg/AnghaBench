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
struct sk_buff {int dummy; } ;
struct rxrpc_call {TYPE_2__* conn; } ;
struct TYPE_4__ {TYPE_1__* security; } ;
struct TYPE_3__ {int (* secure_packet ) (struct rxrpc_call const*,struct sk_buff*,size_t,void*) ;} ;

/* Variables and functions */
 int stub1 (struct rxrpc_call const*,struct sk_buff*,size_t,void*) ; 

int rxrpc_secure_packet(const struct rxrpc_call *call,
			struct sk_buff *skb,
			size_t data_size,
			void *sechdr)
{
	if (call->conn->security)
		return call->conn->security->secure_packet(
			call, skb, data_size, sechdr);
	return 0;
}