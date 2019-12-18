#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  list; int /*<<< orphan*/  cmd_type; } ;
typedef  TYPE_1__ CommandList_struct ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_MSG_STALE ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void removeQ(CommandList_struct *c)
{
	/*
	 * After kexec/dump some commands might still
	 * be in flight, which the firmware will try
	 * to complete. Resetting the firmware doesn't work
	 * with old fw revisions, so we have to mark
	 * them off as 'stale' to prevent the driver from
	 * falling over.
	 */
	if (WARN_ON(list_empty(&c->list))) {
		c->cmd_type = CMD_MSG_STALE;
		return;
	}

	list_del_init(&c->list);
}