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
 char* getexecname () ; 
 char const* pname ; 
 char* strrchr (char const*,char) ; 

const char *
getpname(void)
{
	const char *p, *q;

	if (pname != NULL)
		return (pname);

	if ((p = getexecname()) != NULL)
		q = strrchr(p, '/');
	else
		q = NULL;

	if (q == NULL)
		pname = p;
	else
		pname = q + 1;

	return (pname);
}