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
 scalar_t__ memcmp (char*,char const*,size_t) ; 

__attribute__((used)) static char *
memfind(char *s, const char *find, size_t slen, size_t flen)
{
	int i;

	if (slen == 0 || flen == 0 || flen > slen)
		return (NULL);

	for (i = 0; (size_t) i <= slen - flen; i++) {
		if (s[i] != find[0])
			continue;
		if (flen == 1)
			return (&s[i]);
		if (memcmp(&s[i + 1], &find[1], flen - 1) == 0)
			return (&s[i]);
	}

	return (NULL);
}