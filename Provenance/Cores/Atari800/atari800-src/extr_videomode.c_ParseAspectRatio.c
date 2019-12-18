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
 int FALSE ; 
 int TRUE ; 
 double strtod (char const*,char**) ; 

__attribute__((used)) static int ParseAspectRatio(char const *s, double *w, double *h)
{
	char *s2;
	char *s3;
	*w = strtod(s, &s2);
	if (s2 == s || *w < 0.0)
		return FALSE;
	if (*s2 != ':')
		return FALSE;
	*h = strtod(++s2, &s3);
	if (s3 == s2 || *h < 0.0)
		return FALSE;
	return TRUE;
}