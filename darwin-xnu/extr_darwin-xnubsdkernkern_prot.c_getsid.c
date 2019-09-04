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
struct session {int /*<<< orphan*/  s_sid; } ;
struct getsid_args {scalar_t__ pid; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  proc_find (scalar_t__) ; 
 int /*<<< orphan*/  proc_rele (int /*<<< orphan*/ ) ; 
 struct session* proc_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_rele (struct session*) ; 

int
getsid(proc_t p, struct getsid_args *uap, int32_t *retval)
{
	proc_t pt;
	int refheld = 0;
	struct session * sessp;

	pt = p;
	if (uap->pid == 0)
		goto found;

	if ((pt = proc_find(uap->pid)) == 0)
		return (ESRCH);
	refheld = 1;
found:
	sessp = proc_session(pt);
	*retval = sessp->s_sid;
	session_rele(sessp);

	if (refheld != 0)
		proc_rele(pt);
	return (0);
}