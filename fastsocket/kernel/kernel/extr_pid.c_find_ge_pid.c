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
struct pid_namespace {int dummy; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 struct pid* find_pid_ns (int,struct pid_namespace*) ; 
 int next_pidmap (struct pid_namespace*,int) ; 

struct pid *find_ge_pid(int nr, struct pid_namespace *ns)
{
	struct pid *pid;

	do {
		pid = find_pid_ns(nr, ns);
		if (pid)
			break;
		nr = next_pidmap(ns, nr);
	} while (nr > 0);

	return pid;
}