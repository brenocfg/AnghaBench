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
typedef  int /*<<< orphan*/  u32 ;
struct cipso_v4_doi {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct cipso_v4_doi* cipso_v4_doi_search (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct cipso_v4_doi *cipso_v4_doi_getdef(u32 doi)
{
	struct cipso_v4_doi *doi_def;

	rcu_read_lock();
	doi_def = cipso_v4_doi_search(doi);
	if (doi_def == NULL)
		goto doi_getdef_return;
	if (!atomic_inc_not_zero(&doi_def->refcount))
		doi_def = NULL;

doi_getdef_return:
	rcu_read_unlock();
	return doi_def;
}