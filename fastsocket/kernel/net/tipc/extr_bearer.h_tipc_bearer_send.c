#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tipc_media_addr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct bearer {int /*<<< orphan*/  publ; TYPE_1__* media; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_msg ) (struct sk_buff*,int /*<<< orphan*/ *,struct tipc_media_addr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ *,struct tipc_media_addr*) ; 

__attribute__((used)) static inline int tipc_bearer_send(struct bearer *b_ptr, struct sk_buff *buf,
				   struct tipc_media_addr *dest)
{
	return !b_ptr->media->send_msg(buf, &b_ptr->publ, dest);
}