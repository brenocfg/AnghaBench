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
struct netlbl_dom_map {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlbl_domhsh_def ; 
 struct netlbl_dom_map* netlbl_domhsh_search (char const*) ; 
 struct netlbl_dom_map* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netlbl_dom_map *netlbl_domhsh_search_def(const char *domain)
{
	struct netlbl_dom_map *entry;

	entry = netlbl_domhsh_search(domain);
	if (entry == NULL) {
		entry = rcu_dereference(netlbl_domhsh_def);
		if (entry != NULL && !entry->valid)
			entry = NULL;
	}

	return entry;
}