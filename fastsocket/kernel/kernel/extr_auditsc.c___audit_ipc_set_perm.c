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
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_3__ {unsigned long qbytes; int has_perm; int /*<<< orphan*/  perm_mode; int /*<<< orphan*/  perm_gid; int /*<<< orphan*/  perm_uid; } ;
struct audit_context {TYPE_1__ ipc; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_4__ {struct audit_context* audit_context; } ;

/* Variables and functions */
 TYPE_2__* current ; 

void __audit_ipc_set_perm(unsigned long qbytes, uid_t uid, gid_t gid, mode_t mode)
{
	struct audit_context *context = current->audit_context;

	context->ipc.qbytes = qbytes;
	context->ipc.perm_uid = uid;
	context->ipc.perm_gid = gid;
	context->ipc.perm_mode = mode;
	context->ipc.has_perm = 1;
}