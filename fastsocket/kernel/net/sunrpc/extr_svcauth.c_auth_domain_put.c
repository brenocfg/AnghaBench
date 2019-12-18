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
struct TYPE_3__ {int /*<<< orphan*/  refcount; } ;
struct auth_domain {TYPE_2__* flavour; int /*<<< orphan*/  hash; TYPE_1__ ref; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* domain_release ) (struct auth_domain*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auth_domain_lock ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct auth_domain*) ; 

void auth_domain_put(struct auth_domain *dom)
{
	if (atomic_dec_and_lock(&dom->ref.refcount, &auth_domain_lock)) {
		hlist_del(&dom->hash);
		dom->flavour->domain_release(dom);
		spin_unlock(&auth_domain_lock);
	}
}