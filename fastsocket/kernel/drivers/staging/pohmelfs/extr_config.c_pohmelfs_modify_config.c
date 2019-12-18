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
struct pohmelfs_ctl {int /*<<< orphan*/  prio; int /*<<< orphan*/  perm; } ;

/* Variables and functions */

__attribute__((used)) static int pohmelfs_modify_config(struct pohmelfs_ctl *old, struct pohmelfs_ctl *new)
{
	old->perm = new->perm;
	old->prio = new->prio;
	return 0;
}