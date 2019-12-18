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
struct TYPE_2__ {int /*<<< orphan*/  (* done ) (struct pfkey_sock*) ;int /*<<< orphan*/ * dump; int /*<<< orphan*/ * skb; } ;
struct pfkey_sock {TYPE_1__ dump; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct pfkey_sock*) ; 

__attribute__((used)) static void pfkey_terminate_dump(struct pfkey_sock *pfk)
{
	if (pfk->dump.dump) {
		if (pfk->dump.skb) {
			kfree_skb(pfk->dump.skb);
			pfk->dump.skb = NULL;
		}
		pfk->dump.done(pfk);
		pfk->dump.dump = NULL;
		pfk->dump.done = NULL;
	}
}