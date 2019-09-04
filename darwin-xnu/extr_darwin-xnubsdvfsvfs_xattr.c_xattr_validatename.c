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
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int strlen (char const*) ; 
 scalar_t__ utf8_validatestr (unsigned char const*,int) ; 

int
xattr_validatename(const char *name)
{
	int namelen;

	if (name == NULL || name[0] == '\0') {
		return (EINVAL);
	}
	namelen = strlen(name);
	if (name[namelen] != '\0') 
		return (ENAMETOOLONG);
	
	if (utf8_validatestr((const unsigned char *)name, namelen) != 0) 
		return (EINVAL);
	
	return (0);
}