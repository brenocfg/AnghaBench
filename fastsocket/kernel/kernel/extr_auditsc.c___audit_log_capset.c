#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cred {int /*<<< orphan*/  cap_permitted; int /*<<< orphan*/  cap_effective; } ;
struct TYPE_4__ {int /*<<< orphan*/  permitted; int /*<<< orphan*/  inheritable; int /*<<< orphan*/  effective; } ;
struct TYPE_5__ {TYPE_1__ cap; int /*<<< orphan*/  pid; } ;
struct audit_context {int /*<<< orphan*/  type; TYPE_2__ capset; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_6__ {struct audit_context* audit_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CAPSET ; 
 TYPE_3__* current ; 

void __audit_log_capset(pid_t pid,
		       const struct cred *new, const struct cred *old)
{
	struct audit_context *context = current->audit_context;
	context->capset.pid = pid;
	context->capset.cap.effective   = new->cap_effective;
	context->capset.cap.inheritable = new->cap_effective;
	context->capset.cap.permitted   = new->cap_permitted;
	context->type = AUDIT_CAPSET;
}