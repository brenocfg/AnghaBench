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
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int dump_fit (char*,unsigned long) ; 
 int proc_calc_metrics (char*,char**,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int
read_fit_entry(char *page, char **start, off_t off, int count, int *eof,
	       void *data)
{
	int len;

	/* data holds the NASID of the node */
	len = dump_fit(page, (unsigned long)data);
	len = proc_calc_metrics(page, start, off, count, eof, len);

	return len;
}