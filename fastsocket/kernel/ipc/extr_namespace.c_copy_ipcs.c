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
struct ipc_namespace {int dummy; } ;

/* Variables and functions */
 unsigned long CLONE_NEWIPC ; 
 struct ipc_namespace* create_ipc_ns () ; 
 struct ipc_namespace* get_ipc_ns (struct ipc_namespace*) ; 

struct ipc_namespace *copy_ipcs(unsigned long flags, struct ipc_namespace *ns)
{
	if (!(flags & CLONE_NEWIPC))
		return get_ipc_ns(ns);
	return create_ipc_ns();
}