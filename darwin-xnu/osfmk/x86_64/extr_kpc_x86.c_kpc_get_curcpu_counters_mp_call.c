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
struct kpc_get_counters_remote {int buf_stride; int /*<<< orphan*/  nb_counters; struct kpc_get_counters_remote* buf; int /*<<< orphan*/  classes; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct kpc_get_counters_remote*) ; 
 int cpu_number () ; 
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 int kpc_get_curcpu_counters (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct kpc_get_counters_remote*) ; 

__attribute__((used)) static void
kpc_get_curcpu_counters_mp_call(void *args)
{
	struct kpc_get_counters_remote *handler = args;
	int offset=0, r=0;

	assert(handler);
	assert(handler->buf);

	offset = cpu_number() * handler->buf_stride;
	r = kpc_get_curcpu_counters(handler->classes, NULL, &handler->buf[offset]);

	/* number of counters added by this CPU, needs to be atomic  */
	hw_atomic_add(&(handler->nb_counters), r);
}