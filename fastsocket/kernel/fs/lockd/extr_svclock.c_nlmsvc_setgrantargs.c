#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_8__ {TYPE_1__ oh; int /*<<< orphan*/  svid; int /*<<< orphan*/  caller; int /*<<< orphan*/  fh; int /*<<< orphan*/  fl; } ;
struct TYPE_9__ {TYPE_2__ lock; } ;
struct nlm_rqst {TYPE_3__ a_args; int /*<<< orphan*/ * a_owner; } ;
struct TYPE_10__ {int len; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int /*<<< orphan*/  fl_pid; } ;
struct nlm_lock {TYPE_4__ oh; TYPE_6__ fl; int /*<<< orphan*/  fh; } ;
struct TYPE_11__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NLMCLNT_OHSIZE ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_copy_lock (int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_5__* utsname () ; 

__attribute__((used)) static int nlmsvc_setgrantargs(struct nlm_rqst *call, struct nlm_lock *lock)
{
	locks_copy_lock(&call->a_args.lock.fl, &lock->fl);
	memcpy(&call->a_args.lock.fh, &lock->fh, sizeof(call->a_args.lock.fh));
	call->a_args.lock.caller = utsname()->nodename;
	call->a_args.lock.oh.len = lock->oh.len;

	/* set default data area */
	call->a_args.lock.oh.data = call->a_owner;
	call->a_args.lock.svid = lock->fl.fl_pid;

	if (lock->oh.len > NLMCLNT_OHSIZE) {
		void *data = kmalloc(lock->oh.len, GFP_KERNEL);
		if (!data)
			return 0;
		call->a_args.lock.oh.data = (u8 *) data;
	}

	memcpy(call->a_args.lock.oh.data, lock->oh.data, lock->oh.len);
	return 1;
}