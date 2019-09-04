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

/* Variables and functions */
 size_t MAXTHREADNAMESIZE ; 
 int /*<<< orphan*/  bsd_getthreadname (void*,char*) ; 

int
proc_threadname_kdp(void * uth, char * buf, size_t size)
{
	if (size < MAXTHREADNAMESIZE) {
		/* this is really just a protective measure for the future in
		 * case the thread name size in stackshot gets out of sync with
		 * the BSD max thread name size. Note that bsd_getthreadname
		 * doesn't take input buffer size into account. */
		return -1;
	}

	if (uth != NULL) {
		bsd_getthreadname(uth, buf);
	}
	return 0;
}