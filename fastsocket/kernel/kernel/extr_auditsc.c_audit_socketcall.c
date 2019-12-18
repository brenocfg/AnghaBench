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
struct TYPE_3__ {int nargs; int /*<<< orphan*/  args; } ;
struct audit_context {TYPE_1__ socketcall; int /*<<< orphan*/  type; scalar_t__ dummy; } ;
struct TYPE_4__ {struct audit_context* audit_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SOCKETCALL ; 
 TYPE_2__* current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,int) ; 

void audit_socketcall(int nargs, unsigned long *args)
{
	struct audit_context *context = current->audit_context;

	if (likely(!context || context->dummy))
		return;

	context->type = AUDIT_SOCKETCALL;
	context->socketcall.nargs = nargs;
	memcpy(context->socketcall.args, args, nargs * sizeof(unsigned long));
}