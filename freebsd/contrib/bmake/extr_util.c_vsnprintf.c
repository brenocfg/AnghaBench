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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_6__ {size_t _cnt; int _file; void* _ptr; int /*<<< orphan*/  _flag; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  STRFLAG ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _doprnt (char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  putc (char,TYPE_1__*) ; 
 int vfprintf (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsprintf (char*,char const*,int /*<<< orphan*/ ) ; 

int
vsnprintf(char *s, size_t n, const char *fmt, va_list args)
{
#ifdef STRFLAG
	FILE fakebuf;

	fakebuf._flag = STRFLAG;
	/*
	 * Some os's are char * _ptr, others are unsigned char *_ptr...
	 * We cast to void * to make everyone happy.
	 */
	fakebuf._ptr = (void *)s;
	fakebuf._cnt = n-1;
	fakebuf._file = -1;
	_doprnt(fmt, args, &fakebuf);
	fakebuf._cnt++;
	putc('\0', &fakebuf);
	if (fakebuf._cnt<0)
	    fakebuf._cnt = 0;
	return (n-fakebuf._cnt-1);
#else
#ifndef _PATH_DEVNULL
# define _PATH_DEVNULL "/dev/null"
#endif
	/*
	 * Rats... we don't want to clobber anything...
	 * do a printf to /dev/null to see how much space we need.
	 */
	static FILE *nullfp;
	int need = 0;			/* XXX what's a useful error return? */

	if (!nullfp)
		nullfp = fopen(_PATH_DEVNULL, "w");
	if (nullfp) {
		need = vfprintf(nullfp, fmt, args);
		if (need < n)
			(void)vsprintf(s, fmt, args);
	}
	return need;
#endif
}