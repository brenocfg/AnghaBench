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
typedef  int off_t ;

/* Variables and functions */
 int sprintf (char*,char*,int) ; 
 int uml_exitcode ; 

__attribute__((used)) static int read_proc_exitcode(char *page, char **start, off_t off,
			      int count, int *eof, void *data)
{
	int len, val;

	/*
	 * Save uml_exitcode in a local so that we don't need to guarantee
	 * that sprintf accesses it atomically.
	 */
	val = uml_exitcode;
	len = sprintf(page, "%d\n", val);
	len -= off;
	if (len <= off+count)
		*eof = 1;
	*start = page + off;
	if (len > count)
		len = count;
	if (len < 0)
		len = 0;
	return len;
}