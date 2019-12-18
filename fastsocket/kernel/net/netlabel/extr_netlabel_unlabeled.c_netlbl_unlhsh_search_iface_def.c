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
struct netlbl_unlhsh_iface {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlbl_unlhsh_def ; 
 struct netlbl_unlhsh_iface* netlbl_unlhsh_search_iface (int) ; 
 struct netlbl_unlhsh_iface* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct netlbl_unlhsh_iface *netlbl_unlhsh_search_iface_def(int ifindex)
{
	struct netlbl_unlhsh_iface *entry;

	entry = netlbl_unlhsh_search_iface(ifindex);
	if (entry != NULL)
		return entry;

	entry = rcu_dereference(netlbl_unlhsh_def);
	if (entry != NULL && entry->valid)
		return entry;

	return NULL;
}