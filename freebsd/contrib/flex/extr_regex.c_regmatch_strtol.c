#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rm_so; } ;
typedef  TYPE_1__ regmatch_t ;

/* Variables and functions */
 int bufsz ; 
 int /*<<< orphan*/  free (char*) ; 
 char* regmatch_cpy (TYPE_1__*,char*,char const*) ; 
 char* regmatch_dup (TYPE_1__*,char const*) ; 
 int regmatch_len (TYPE_1__*) ; 
 int strtol (char*,char**,int) ; 

int regmatch_strtol (regmatch_t * m, const char *src, char **endptr,
		     int base)
{
	int     n = 0;

#define bufsz 20
	char    buf[bufsz];
	char   *s;

	if (m == NULL || m->rm_so < 0)
		return 0;

	if (regmatch_len (m) < bufsz)
		s = regmatch_cpy (m, buf, src);
	else
		s = regmatch_dup (m, src);

	n = strtol (s, endptr, base);

	if (s != buf)
		free (s);

	return n;
}