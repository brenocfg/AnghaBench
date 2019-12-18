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
 int strlen (char const*) ; 

__attribute__((used)) static int tomoyo_path_depth(const char *pathname)
{
	int i = 0;

	if (pathname) {
		const char *ep = pathname + strlen(pathname);
		if (pathname < ep--) {
			if (*ep != '/')
				i++;
			while (pathname <= ep)
				if (*ep-- == '/')
					i += 2;
		}
	}
	return i;
}