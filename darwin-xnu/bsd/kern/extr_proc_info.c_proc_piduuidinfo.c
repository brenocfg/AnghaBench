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
typedef  scalar_t__ uuid_t ;
typedef  int uint32_t ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 struct proc* PROC_NULL ; 
 int /*<<< orphan*/  proc_drop_zombref (struct proc*) ; 
 struct proc* proc_find (int /*<<< orphan*/ ) ; 
 struct proc* proc_find_zombref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_getexecutableuuid (struct proc*,unsigned char*,int) ; 
 int /*<<< orphan*/  proc_rele (struct proc*) ; 

__attribute__((used)) static int
proc_piduuidinfo(pid_t pid, uuid_t uuid_buf, uint32_t buffersize)
{
	struct proc * p = PROC_NULL;
	int zombref = 0;

	if (buffersize < sizeof(uuid_t))
		return EINVAL;

	if ((p = proc_find(pid)) == PROC_NULL) {
		p = proc_find_zombref(pid);
		zombref = 1;
	}
	if (p == PROC_NULL) {
		return ESRCH;
	}

	proc_getexecutableuuid(p, (unsigned char *)uuid_buf, buffersize);

	if (zombref)
		proc_drop_zombref(p);
	else
		proc_rele(p);

	return 0;
}