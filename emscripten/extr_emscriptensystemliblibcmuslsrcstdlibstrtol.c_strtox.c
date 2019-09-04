#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* rend; int lock; void* rpos; void* buf; scalar_t__ flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 unsigned long long __intscan (TYPE_1__*,int,int,unsigned long long) ; 
 size_t shcnt (TYPE_1__*) ; 
 int /*<<< orphan*/  shlim (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long long strtox(const char *s, char **p, int base, unsigned long long lim)
{
	/* FIXME: use a helper function or macro to setup the FILE */
	FILE f;
	f.flags = 0;
	f.buf = f.rpos = (void *)s;
	if ((size_t)s > (size_t)-1/2)
		f.rend = (void *)-1;
	else
		f.rend = (unsigned char *)s+(size_t)-1/2;
	f.lock = -1;
	shlim(&f, 0);
	unsigned long long y = __intscan(&f, base, 1, lim);
	if (p) {
		size_t cnt = shcnt(&f);
		*p = (char *)s + cnt;
	}
	return y;
}