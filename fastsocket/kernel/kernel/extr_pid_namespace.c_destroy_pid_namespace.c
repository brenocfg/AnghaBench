#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pid_namespace {TYPE_1__* pidmap; int /*<<< orphan*/  proc_inum; } ;
struct TYPE_2__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int PIDMAP_ENTRIES ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct pid_namespace*) ; 
 int /*<<< orphan*/  pid_ns_cachep ; 
 int /*<<< orphan*/  proc_free_inum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_pid_namespace(struct pid_namespace *ns)
{
	int i;

	proc_free_inum(ns->proc_inum);
	for (i = 0; i < PIDMAP_ENTRIES; i++)
		kfree(ns->pidmap[i].page);
	kmem_cache_free(pid_ns_cachep, ns);
}