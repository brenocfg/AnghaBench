#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ uint32_t ;
struct fileport_info_args {int fia_flavor; int /*<<< orphan*/ * fia_retval; scalar_t__ fia_buffersize; int /*<<< orphan*/  fia_buffer; } ;
typedef  TYPE_1__* proc_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SAME_USER ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int ESRCH ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  PROC_INFO_CALL_PIDFILEPORTINFO ; 
 TYPE_1__* PROC_NULL ; 
#define  PROC_PIDFILEPORTPIPEINFO 131 
 scalar_t__ PROC_PIDFILEPORTPIPEINFO_SIZE ; 
#define  PROC_PIDFILEPORTPSHMINFO 130 
 scalar_t__ PROC_PIDFILEPORTPSHMINFO_SIZE ; 
#define  PROC_PIDFILEPORTSOCKETINFO 129 
 scalar_t__ PROC_PIDFILEPORTSOCKETINFO_SIZE ; 
#define  PROC_PIDFILEPORTVNODEPATHINFO 128 
 scalar_t__ PROC_PIDFILEPORTVNODEPATHINFO_SIZE ; 
 scalar_t__ fileport_invoke (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fileport_info_args*,int*) ; 
 int /*<<< orphan*/  proc_fileport_info ; 
 TYPE_1__* proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (TYPE_1__*) ; 
 int proc_security_policy (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
proc_pidfileportinfo(int pid, int flavor, mach_port_name_t name,
	user_addr_t buffer, uint32_t buffersize, int32_t *retval)
{
	proc_t p;
	int error = ENOTSUP;
	uint32_t size;
	struct fileport_info_args fia;

	/* fileport types are restricted by file_issendable() */

	switch (flavor) {
	case PROC_PIDFILEPORTVNODEPATHINFO:
		size = PROC_PIDFILEPORTVNODEPATHINFO_SIZE;
		break;
	case PROC_PIDFILEPORTSOCKETINFO:
		size = PROC_PIDFILEPORTSOCKETINFO_SIZE;
		break;
	case PROC_PIDFILEPORTPSHMINFO:
		size = PROC_PIDFILEPORTPSHMINFO_SIZE;
		break;
	case PROC_PIDFILEPORTPIPEINFO:
		size = PROC_PIDFILEPORTPIPEINFO_SIZE;
		break;
	default:
		return (EINVAL);
	}
 
	if (buffersize < size)
		return (ENOMEM);
	if ((p = proc_find(pid)) == PROC_NULL) {
		error = ESRCH;
		goto out;
	}

	/* Do we have permission to look into this? */
	if ((error = proc_security_policy(p, PROC_INFO_CALL_PIDFILEPORTINFO, flavor, CHECK_SAME_USER)))
		goto out1;

	fia.fia_flavor = flavor;
	fia.fia_buffer = buffer;
	fia.fia_buffersize = buffersize;
	fia.fia_retval = retval;

	if (fileport_invoke(p->task, name,
	    proc_fileport_info, &fia, &error) != KERN_SUCCESS)
		error = EINVAL;
out1:
	proc_rele(p);
out:
	return (error);
}