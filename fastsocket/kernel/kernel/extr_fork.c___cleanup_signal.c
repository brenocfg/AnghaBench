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
struct signal_struct {int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct signal_struct*) ; 
 int /*<<< orphan*/  sched_autogroup_exit (struct signal_struct*) ; 
 int /*<<< orphan*/  signal_cachep ; 
 int /*<<< orphan*/  thread_group_cputime_free (struct signal_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (int /*<<< orphan*/ ) ; 

void __cleanup_signal(struct signal_struct *sig)
{
	thread_group_cputime_free(sig);
	tty_kref_put(sig->tty);
	sched_autogroup_exit(sig);
	kmem_cache_free(signal_cachep, sig);
}