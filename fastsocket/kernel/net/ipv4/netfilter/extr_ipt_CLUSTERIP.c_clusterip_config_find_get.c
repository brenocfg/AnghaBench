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
struct clusterip_config {int /*<<< orphan*/  entries; int /*<<< orphan*/  refcount; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 struct clusterip_config* __clusterip_config_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterip_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct clusterip_config *
clusterip_config_find_get(__be32 clusterip, int entry)
{
	struct clusterip_config *c;

	read_lock_bh(&clusterip_lock);
	c = __clusterip_config_find(clusterip);
	if (!c) {
		read_unlock_bh(&clusterip_lock);
		return NULL;
	}
	atomic_inc(&c->refcount);
	if (entry)
		atomic_inc(&c->entries);
	read_unlock_bh(&clusterip_lock);

	return c;
}