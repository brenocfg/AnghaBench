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
struct ip_vs_lblcr_entry {int /*<<< orphan*/  set; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_vs_dest_set_eraseall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ip_vs_lblcr_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ip_vs_lblcr_free(struct ip_vs_lblcr_entry *en)
{
	list_del(&en->list);
	ip_vs_dest_set_eraseall(&en->set);
	kfree(en);
}