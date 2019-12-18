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
struct ipip_net {int dummy; } ;
struct ip_tunnel {struct ip_tunnel* next; } ;

/* Variables and functions */
 struct ip_tunnel** ipip_bucket (struct ipip_net*,struct ip_tunnel*) ; 
 int /*<<< orphan*/  ipip_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipip_tunnel_link(struct ipip_net *ipn, struct ip_tunnel *t)
{
	struct ip_tunnel **tp = ipip_bucket(ipn, t);

	t->next = *tp;
	write_lock_bh(&ipip_lock);
	*tp = t;
	write_unlock_bh(&ipip_lock);
}