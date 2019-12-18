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
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int EINVAL ; 
 int sym_host_info (struct Scsi_Host*,char*,int /*<<< orphan*/ ,int) ; 
 int sym_user_command (struct Scsi_Host*,char*,int) ; 

__attribute__((used)) static int sym53c8xx_proc_info(struct Scsi_Host *shost, char *buffer,
			char **start, off_t offset, int length, int func)
{
	int retv;

	if (func) {
#ifdef	SYM_LINUX_USER_COMMAND_SUPPORT
		retv = sym_user_command(shost, buffer, length);
#else
		retv = -EINVAL;
#endif
	} else {
		if (start)
			*start = buffer;
#ifdef SYM_LINUX_USER_INFO_SUPPORT
		retv = sym_host_info(shost, buffer, offset, length);
#else
		retv = -EINVAL;
#endif
	}

	return retv;
}