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
struct kpc_get_counters_remote {int buf_stride; int /*<<< orphan*/  nb_counters; int /*<<< orphan*/ * buf; int /*<<< orphan*/  classes; } ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ hw_atomic_sub (int /*<<< orphan*/ *,int) ; 
 int kpc_get_curcpu_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kpc_xread_sync ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kpc_get_curcpu_counters_xcall(void *args)
{
	struct kpc_get_counters_remote *handler = args;

	assert(handler != NULL);
	assert(handler->buf != NULL);

	int offset = cpu_number() * handler->buf_stride;
	int r = kpc_get_curcpu_counters(handler->classes, NULL, &handler->buf[offset]);

	/* number of counters added by this CPU, needs to be atomic  */
	hw_atomic_add(&(handler->nb_counters), r);

	if (hw_atomic_sub(&kpc_xread_sync, 1) == 0) {
		thread_wakeup((event_t) &kpc_xread_sync);
	}
}