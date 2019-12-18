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
typedef  int /*<<< orphan*/  banner ;

/* Variables and functions */
 scalar_t__ FIT_ENTRY_SAL_A ; 
 int FIT_MAJOR (unsigned long) ; 
 int FIT_MINOR (unsigned long) ; 
 scalar_t__ FIT_TYPE (unsigned long) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ get_fit_entry (unsigned long,int,unsigned long*,char*,int) ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,char*) ; 
 int sprintf (char*,char*,int,int) ; 

__attribute__((used)) static int
dump_version(char *page, unsigned long nasid)
{
	unsigned long fentry[2];
	char banner[128];
	int index;
	int len;

	for (index = 0; ; index++) {
		if (get_fit_entry(nasid, index, fentry, banner,
				  sizeof(banner)))
			return 0;
		if (FIT_TYPE(fentry[1]) == FIT_ENTRY_SAL_A)
			break;
	}

	len = sprintf(page, "%x.%02x\n", FIT_MAJOR(fentry[1]),
		      FIT_MINOR(fentry[1]));
	page += len;

	if (banner[0])
		len += snprintf(page, PAGE_SIZE-len, "%s\n", banner);

	return len;
}