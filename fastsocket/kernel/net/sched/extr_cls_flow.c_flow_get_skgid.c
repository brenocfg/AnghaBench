#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {TYPE_4__* sk; } ;
struct TYPE_8__ {TYPE_3__* sk_socket; } ;
struct TYPE_7__ {TYPE_2__* file; } ;
struct TYPE_6__ {TYPE_1__* f_cred; } ;
struct TYPE_5__ {int /*<<< orphan*/  fsgid; } ;

/* Variables and functions */

__attribute__((used)) static u32 flow_get_skgid(const struct sk_buff *skb)
{
	if (skb->sk && skb->sk->sk_socket && skb->sk->sk_socket->file)
		return skb->sk->sk_socket->file->f_cred->fsgid;
	return 0;
}