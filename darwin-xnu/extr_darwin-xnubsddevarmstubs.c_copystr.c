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
 int ENAMETOOLONG ; 

int
copystr(const void *vfrom, void *vto, size_t maxlen, size_t * lencopied)
{
	size_t          l;
	char const     *from = (char const *) vfrom;
	char           *to = (char *) vto;

	for (l = 0; l < maxlen; l++) {
		if ((*to++ = *from++) == '\0') {
			if (lencopied)
				*lencopied = l + 1;
			return 0;
		}
	}
	if (lencopied)
		*lencopied = maxlen;
	return ENAMETOOLONG;
}