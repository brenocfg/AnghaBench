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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_5__ {unsigned char* buf; int buf_size; int lock; void* cookie; int /*<<< orphan*/  read; scalar_t__ rend; scalar_t__ rpos; scalar_t__ flags; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 long double __floatscan (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  do_read ; 
 scalar_t__ iswspace (int /*<<< orphan*/ ) ; 
 size_t shcnt (TYPE_1__*) ; 
 int /*<<< orphan*/  shlim (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long double wcstox(const wchar_t *s, wchar_t **p, int prec)
{
	wchar_t *t = (wchar_t *)s;
	unsigned char buf[64];
	FILE f = {0};
	f.flags = 0;
	f.rpos = f.rend = 0;
	f.buf = buf + 4;
	f.buf_size = sizeof buf - 4;
	f.lock = -1;
	f.read = do_read;
	while (iswspace(*t)) t++;
	f.cookie = (void *)t;
	shlim(&f, 0);
	long double y = __floatscan(&f, prec, 1);
	if (p) {
		size_t cnt = shcnt(&f);
		*p = cnt ? t + cnt : (wchar_t *)s;
	}
	return y;
}