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
struct netlink_callback {int* args; void* done; } ;
struct fib6_walker_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_walker_unlink (struct fib6_walker_t*) ; 
 int /*<<< orphan*/  kfree (struct fib6_walker_t*) ; 

__attribute__((used)) static void fib6_dump_end(struct netlink_callback *cb)
{
	struct fib6_walker_t *w = (void*)cb->args[2];

	if (w) {
		if (cb->args[4]) {
			cb->args[4] = 0;
			fib6_walker_unlink(w);
		}
		cb->args[2] = 0;
		kfree(w);
	}
	cb->done = (void*)cb->args[3];
	cb->args[1] = 3;
}