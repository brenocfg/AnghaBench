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
struct ip_tunnel_prl_entry {scalar_t__ addr; int /*<<< orphan*/  flags; struct ip_tunnel_prl_entry* next; } ;
struct ip_tunnel_prl {scalar_t__ addr; int /*<<< orphan*/  flags; } ;
struct ip_tunnel {int /*<<< orphan*/  prl_count; struct ip_tunnel_prl_entry* prl; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipip6_lock ; 
 struct ip_tunnel_prl_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipip6_tunnel_add_prl(struct ip_tunnel *t, struct ip_tunnel_prl *a, int chg)
{
	struct ip_tunnel_prl_entry *p;
	int err = 0;

	if (a->addr == htonl(INADDR_ANY))
		return -EINVAL;

	write_lock(&ipip6_lock);

	for (p = t->prl; p; p = p->next) {
		if (p->addr == a->addr) {
			if (chg)
				goto update;
			err = -EEXIST;
			goto out;
		}
	}

	if (chg) {
		err = -ENXIO;
		goto out;
	}

	p = kzalloc(sizeof(struct ip_tunnel_prl_entry), GFP_KERNEL);
	if (!p) {
		err = -ENOBUFS;
		goto out;
	}

	p->next = t->prl;
	t->prl = p;
	t->prl_count++;
update:
	p->addr = a->addr;
	p->flags = a->flags;
out:
	write_unlock(&ipip6_lock);
	return err;
}