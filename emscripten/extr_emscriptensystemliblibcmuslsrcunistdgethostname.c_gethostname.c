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
struct utsname {char* nodename; } ;

/* Variables and functions */
 scalar_t__ uname (struct utsname*) ; 

int gethostname(char *name, size_t len)
{
	size_t i;
	struct utsname uts;
	if (uname(&uts)) return -1;
	if (len > sizeof uts.nodename) len = sizeof uts.nodename;
	for (i=0; i<len && (name[i] = uts.nodename[i]); i++);
	if (i==len) name[i-1] = 0;
	return 0;
}