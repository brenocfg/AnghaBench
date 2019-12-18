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
struct notifier_block {int dummy; } ;
struct die_args {int err; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 unsigned long DIE_DEBUG ; 
 int DR_STEP ; 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int post_kmmio_handler (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kmmio_die_notifier(struct notifier_block *nb, unsigned long val, void *args)
{
	struct die_args *arg = args;

	if (val == DIE_DEBUG && (arg->err & DR_STEP))
		if (post_kmmio_handler(arg->err, arg->regs) == 1)
			return NOTIFY_STOP;

	return NOTIFY_DONE;
}