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
struct sit_net {int dummy; } ;
struct ip_tunnel {struct ip_tunnel* next; } ;

/* Variables and functions */
 struct ip_tunnel** ipip6_bucket (struct sit_net*,struct ip_tunnel*) ; 
 int /*<<< orphan*/  ipip6_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipip6_tunnel_link(struct sit_net *sitn, struct ip_tunnel *t)
{
	struct ip_tunnel **tp = ipip6_bucket(sitn, t);

	t->next = *tp;
	write_lock_bh(&ipip6_lock);
	*tp = t;
	write_unlock_bh(&ipip6_lock);
}