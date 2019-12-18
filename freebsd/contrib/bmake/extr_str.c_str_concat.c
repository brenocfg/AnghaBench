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
 int STR_ADDSLASH ; 
 int STR_ADDSPACE ; 
 char* bmake_malloc (unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

char *
str_concat(const char *s1, const char *s2, int flags)
{
	int len1, len2;
	char *result;

	/* get the length of both strings */
	len1 = strlen(s1);
	len2 = strlen(s2);

	/* allocate length plus separator plus EOS */
	result = bmake_malloc((unsigned int)(len1 + len2 + 2));

	/* copy first string into place */
	memcpy(result, s1, len1);

	/* add separator character */
	if (flags & STR_ADDSPACE) {
		result[len1] = ' ';
		++len1;
	} else if (flags & STR_ADDSLASH) {
		result[len1] = '/';
		++len1;
	}

	/* copy second string plus EOS into place */
	memcpy(result + len1, s2, len2 + 1);

	return(result);
}