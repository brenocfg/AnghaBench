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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  PROC_INFO_CALL_PIDINFO ; 
 int /*<<< orphan*/  PROC_PIDPATHINFO ; 
 scalar_t__ PROC_PIDPATHINFO_MAXSIZE ; 
 scalar_t__ PROC_PIDPATHINFO_SIZE ; 
 int __proc_info (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ strlen (void*) ; 

int
proc_pidpath(int pid, void * buffer, uint32_t  buffersize)
{
	int retval, len;

	if (buffersize < PROC_PIDPATHINFO_SIZE) {
		errno = ENOMEM;
		return(0);
	}
	if (buffersize >  PROC_PIDPATHINFO_MAXSIZE) {
		errno = EOVERFLOW;
		return(0);
	}

	retval = __proc_info(PROC_INFO_CALL_PIDINFO, pid, PROC_PIDPATHINFO,  (uint64_t)0,  buffer, buffersize);
	if (retval != -1) {
		len = (int)strlen(buffer);
		return(len);
	}
	return (0);
}