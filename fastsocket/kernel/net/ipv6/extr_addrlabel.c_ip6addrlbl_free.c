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
struct ip6addrlbl_entry {int /*<<< orphan*/  lbl_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ip6addrlbl_entry*) ; 
 int /*<<< orphan*/  release_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ip6addrlbl_free(struct ip6addrlbl_entry *p)
{
#ifdef CONFIG_NET_NS
	release_net(p->lbl_net);
#endif
	kfree(p);
}