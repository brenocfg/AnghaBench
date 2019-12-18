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
struct ip_tunnel_prl_entry {scalar_t__ addr; struct ip_tunnel_prl_entry* next; } ;
struct ip_tunnel_prl {scalar_t__ addr; } ;
struct ip_tunnel {int /*<<< orphan*/  prl_count; struct ip_tunnel_prl_entry* prl; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip6_lock ; 
 int /*<<< orphan*/  kfree (struct ip_tunnel_prl_entry*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipip6_tunnel_del_prl(struct ip_tunnel *t, struct ip_tunnel_prl *a)
{
	struct ip_tunnel_prl_entry *x, **p;
	int err = 0;

	write_lock(&ipip6_lock);

	if (a && a->addr != htonl(INADDR_ANY)) {
		for (p = &t->prl; *p; p = &(*p)->next) {
			if ((*p)->addr == a->addr) {
				x = *p;
				*p = x->next;
				kfree(x);
				t->prl_count--;
				goto out;
			}
		}
		err = -ENXIO;
	} else {
		while (t->prl) {
			x = t->prl;
			t->prl = t->prl->next;
			kfree(x);
			t->prl_count--;
		}
	}
out:
	write_unlock(&ipip6_lock);
	return err;
}