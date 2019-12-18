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
 int FSTAR ; 
 int getnum (char const*,size_t,int,int*,char*,char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int
getmask(const char *f, size_t l, bool local, const char **p, int *mask)
{
	char *d;
	const char *s = *p; 

	if ((d = strchr(s, ':')) != NULL) {
		*d++ = '\0';
		*p = d;
	}
	if ((d = strchr(s, '/')) == NULL) {
		*mask = FSTAR;
		return 0;
	}

	*d++ = '\0';
	return getnum(f, l, local, mask, "mask", d);
}