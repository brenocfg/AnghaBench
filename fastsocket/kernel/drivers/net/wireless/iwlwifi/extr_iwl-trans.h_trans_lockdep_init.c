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
struct lock_class_key {int dummy; } ;
struct iwl_trans {int /*<<< orphan*/  sync_cmd_lockdep_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_init_map (int /*<<< orphan*/ *,char*,struct lock_class_key*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void trans_lockdep_init(struct iwl_trans *trans)
{
#ifdef CONFIG_LOCKDEP
	static struct lock_class_key __key;

	lockdep_init_map(&trans->sync_cmd_lockdep_map, "sync_cmd_lockdep_map",
			 &__key, 0);
#endif
}