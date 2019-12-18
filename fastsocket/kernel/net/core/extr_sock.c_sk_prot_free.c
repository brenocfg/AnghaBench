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
struct sock {int dummy; } ;
struct proto {struct kmem_cache* slab; struct module* owner; } ;
struct module {int dummy; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sock*) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct sock*) ; 
 int /*<<< orphan*/  module_put (struct module*) ; 
 int /*<<< orphan*/  security_sk_free (struct sock*) ; 

__attribute__((used)) static void sk_prot_free(struct proto *prot, struct sock *sk)
{
	struct kmem_cache *slab;
	struct module *owner;

	owner = prot->owner;
	slab = prot->slab;

	security_sk_free(sk);
	if (slab != NULL)
		kmem_cache_free(slab, sk);
	else
		kfree(sk);
	module_put(owner);
}