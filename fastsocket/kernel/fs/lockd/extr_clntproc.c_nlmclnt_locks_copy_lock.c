#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* owner; int /*<<< orphan*/  list; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_3__ nfs_fl; } ;
struct file_lock {TYPE_2__ fl_u; } ;
struct TYPE_9__ {TYPE_1__* host; } ;
struct TYPE_6__ {int /*<<< orphan*/  h_granted; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__* nlm_get_lockowner (TYPE_4__*) ; 

__attribute__((used)) static void nlmclnt_locks_copy_lock(struct file_lock *new, struct file_lock *fl)
{
	new->fl_u.nfs_fl.state = fl->fl_u.nfs_fl.state;
	new->fl_u.nfs_fl.owner = nlm_get_lockowner(fl->fl_u.nfs_fl.owner);
	list_add_tail(&new->fl_u.nfs_fl.list, &fl->fl_u.nfs_fl.owner->host->h_granted);
}