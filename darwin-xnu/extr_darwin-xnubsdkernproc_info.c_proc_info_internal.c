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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int /*<<< orphan*/  kqueue_id_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EINVAL ; 
#define  PROC_INFO_CALL_CANUSEFGHW 141 
#define  PROC_INFO_CALL_DIRTYCONTROL 140 
#define  PROC_INFO_CALL_KERNMSGBUF 139 
#define  PROC_INFO_CALL_LISTCOALITIONS 138 
#define  PROC_INFO_CALL_LISTPIDS 137 
#define  PROC_INFO_CALL_PIDDYNKQUEUEINFO 136 
#define  PROC_INFO_CALL_PIDFDINFO 135 
#define  PROC_INFO_CALL_PIDFILEPORTINFO 134 
#define  PROC_INFO_CALL_PIDINFO 133 
#define  PROC_INFO_CALL_PIDORIGINATORINFO 132 
#define  PROC_INFO_CALL_PIDRUSAGE 131 
#define  PROC_INFO_CALL_SETCONTROL 130 
#define  PROC_INFO_CALL_TERMINATE 129 
#define  PROC_INFO_CALL_UDATA_INFO 128 
 int proc_can_use_foreground_hw (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_dirtycontrol (int,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int proc_kernmsgbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_listcoalitions (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_listpids (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_pid_rusage (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_piddynkqueueinfo (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_pidfdinfo (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_pidfileportinfo (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_pidinfo (int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_pidoriginatorinfo (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_setcontrol (int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proc_terminate (int,int /*<<< orphan*/ *) ; 
 int proc_udata_info (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int 
proc_info_internal(int callnum, int pid, int flavor, uint64_t arg, user_addr_t buffer, uint32_t  buffersize, int32_t * retval)
{

	switch(callnum) {
		case PROC_INFO_CALL_LISTPIDS:
			/* pid contains type and flavor contains typeinfo */
			return(proc_listpids(pid, flavor, buffer, buffersize, retval));
		case PROC_INFO_CALL_PIDINFO:
			return(proc_pidinfo(pid, flavor, arg, buffer, buffersize, retval));
		case PROC_INFO_CALL_PIDFDINFO:
			return(proc_pidfdinfo(pid, flavor, (int)arg, buffer, buffersize, retval));
		case PROC_INFO_CALL_KERNMSGBUF:
			return(proc_kernmsgbuf(buffer, buffersize, retval));
		case PROC_INFO_CALL_SETCONTROL:
			return(proc_setcontrol(pid, flavor, arg, buffer, buffersize, retval));
		case PROC_INFO_CALL_PIDFILEPORTINFO:
			return(proc_pidfileportinfo(pid, flavor, (mach_port_name_t)arg, buffer, buffersize, retval));
		case PROC_INFO_CALL_TERMINATE:
			return(proc_terminate(pid, retval));
		case PROC_INFO_CALL_DIRTYCONTROL:
			return(proc_dirtycontrol(pid, flavor, arg, retval));
		case PROC_INFO_CALL_PIDRUSAGE:
			return (proc_pid_rusage(pid, flavor, buffer, retval));
		case PROC_INFO_CALL_PIDORIGINATORINFO:
			return (proc_pidoriginatorinfo(pid, flavor, buffer, buffersize, retval));
		case PROC_INFO_CALL_LISTCOALITIONS:
			return proc_listcoalitions(pid /* flavor */, flavor /* coaltype */, buffer,
						   buffersize, retval);
		case PROC_INFO_CALL_CANUSEFGHW:
			return proc_can_use_foreground_hw(pid, buffer, buffersize, retval);
		case PROC_INFO_CALL_PIDDYNKQUEUEINFO:
			return proc_piddynkqueueinfo(pid, flavor, (kqueue_id_t)arg, buffer, buffersize, retval);
#if !CONFIG_EMBEDDED
		case PROC_INFO_CALL_UDATA_INFO:
			return proc_udata_info(pid, flavor, buffer, buffersize, retval);
#endif /* !CONFIG_EMBEDDED */
		default:
			return EINVAL;
	}

	return(EINVAL);
}