#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {TYPE_1__ nfs_fl; } ;
struct file_lock {TYPE_2__ fl_u; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_put_lockowner (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nlmclnt_locks_release_private(struct file_lock *fl)
{
	list_del(&fl->fl_u.nfs_fl.list);
	nlm_put_lockowner(fl->fl_u.nfs_fl.owner);
}