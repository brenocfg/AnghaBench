#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct getpgid_args {scalar_t__ pid; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  p_pgrpid; } ;

/* Variables and functions */
 int ESRCH ; 
 TYPE_1__* proc_find (scalar_t__) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 

int
getpgid(proc_t p, struct getpgid_args *uap, int32_t *retval)
{
	proc_t pt;
	int refheld = 0;

	pt = p;
	if (uap->pid == 0)
		goto found;

	if ((pt = proc_find(uap->pid)) == 0)
		return (ESRCH);
	refheld = 1;
found:
	*retval = pt->p_pgrpid;
	if (refheld != 0)
		proc_rele(pt);
	return (0);
}