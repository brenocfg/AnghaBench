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
struct spwd {char* sp_namp; char* sp_pwdp; void* sp_flag; void* sp_expire; void* sp_inact; void* sp_warn; void* sp_max; void* sp_min; void* sp_lstchg; } ;

/* Variables and functions */
 char* strchr (char*,char) ; 
 void* xatol (char**) ; 

int __parsespent(char *s, struct spwd *sp)
{
	sp->sp_namp = s;
	if (!(s = strchr(s, ':'))) return -1;
	*s = 0;

	sp->sp_pwdp = ++s;
	if (!(s = strchr(s, ':'))) return -1;
	*s = 0;

	s++; sp->sp_lstchg = xatol(&s);
	if (*s != ':') return -1;

	s++; sp->sp_min = xatol(&s);
	if (*s != ':') return -1;

	s++; sp->sp_max = xatol(&s);
	if (*s != ':') return -1;

	s++; sp->sp_warn = xatol(&s);
	if (*s != ':') return -1;

	s++; sp->sp_inact = xatol(&s);
	if (*s != ':') return -1;

	s++; sp->sp_expire = xatol(&s);
	if (*s != ':') return -1;

	s++; sp->sp_flag = xatol(&s);
	if (*s != '\n') return -1;
	return 0;
}