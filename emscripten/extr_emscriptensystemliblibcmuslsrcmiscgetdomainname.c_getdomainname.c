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
struct utsname {int /*<<< orphan*/  domainname; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uname (struct utsname*) ; 

int getdomainname(char *name, size_t len)
{
	struct utsname temp;
	uname(&temp);
	if (!len || strlen(temp.domainname) >= len) {
		errno = EINVAL;
		return -1;
	}
	strcpy(name, temp.domainname);
	return 0;
}