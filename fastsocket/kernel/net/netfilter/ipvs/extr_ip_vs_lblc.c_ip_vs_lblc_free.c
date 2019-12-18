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
struct ip_vs_lblc_entry {TYPE_1__* dest; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ip_vs_lblc_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ip_vs_lblc_free(struct ip_vs_lblc_entry *en)
{
	list_del(&en->list);
	/*
	 * We don't kfree dest because it is refered either by its service
	 * or the trash dest list.
	 */
	atomic_dec(&en->dest->refcnt);
	kfree(en);
}