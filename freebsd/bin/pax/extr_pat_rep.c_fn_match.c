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
 int dflag ; 
 char* range_match (char*,char) ; 

__attribute__((used)) static int
fn_match(char *pattern, char *string, char **pend)
{
	char c;
	char test;

	*pend = NULL;
	for (;;) {
		switch (c = *pattern++) {
		case '\0':
			/*
			 * Ok we found an exact match
			 */
			if (*string == '\0')
				return(0);

			/*
			 * Check if it is a prefix match
			 */
			if ((dflag == 1) || (*string != '/'))
				return(-1);

			/*
			 * It is a prefix match, remember where the trailing
			 * / is located
			 */
			*pend = string;
			return(0);
		case '?':
			if ((test = *string++) == '\0')
				return (-1);
			break;
		case '*':
			c = *pattern;
			/*
			 * Collapse multiple *'s.
			 */
			while (c == '*')
				c = *++pattern;

			/*
			 * Optimized hack for pattern with a * at the end
			 */
			if (c == '\0')
				return (0);

			/*
			 * General case, use recursion.
			 */
			while ((test = *string) != '\0') {
				if (!fn_match(pattern, string, pend))
					return (0);
				++string;
			}
			return (-1);
		case '[':
			/*
			 * range match
			 */
			if (((test = *string++) == '\0') ||
			    ((pattern = range_match(pattern, test)) == NULL))
				return (-1);
			break;
		case '\\':
		default:
			if (c != *string++)
				return (-1);
			break;
		}
	}
	/* NOTREACHED */
}