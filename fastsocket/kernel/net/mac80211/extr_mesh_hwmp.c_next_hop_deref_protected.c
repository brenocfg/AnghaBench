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
struct sta_info {int dummy; } ;
struct mesh_path {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  next_hop; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct sta_info* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sta_info *
next_hop_deref_protected(struct mesh_path *mpath)
{
	return rcu_dereference_protected(mpath->next_hop,
					 lockdep_is_held(&mpath->state_lock));
}