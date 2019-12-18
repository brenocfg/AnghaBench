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
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_tunnel {int /*<<< orphan*/  (* err_handler ) (struct sk_buff*,int /*<<< orphan*/ ) ;struct xfrm_tunnel* next; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct xfrm_tunnel* tunnel4_handlers ; 

__attribute__((used)) static void tunnel4_err(struct sk_buff *skb, u32 info)
{
	struct xfrm_tunnel *handler;

	for (handler = tunnel4_handlers; handler; handler = handler->next)
		if (!handler->err_handler(skb, info))
			break;
}