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
struct string {int len; char* str; struct string* link; } ;

/* Variables and functions */
 int NELEMS (struct string**) ; 
 int /*<<< orphan*/  NEW (struct string*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
 char* allocate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 struct string** buckets ; 
 unsigned int* scatter ; 

char *stringn(const char *str, int len) {
	int i;
	unsigned int h;
	const char *end;
	struct string *p;

	assert(str);
	for (h = 0, i = len, end = str; i > 0; i--)
		h = (h<<1) + scatter[*(unsigned char *)end++];
	h &= NELEMS(buckets)-1;
	for (p = buckets[h]; p; p = p->link)
		if (len == p->len) {
			const char *s1 = str;
			char *s2 = p->str;
			do {
				if (s1 == end)
					return p->str;
			} while (*s1++ == *s2++);
		}
	{
		static char *next, *strlimit;
		if (len + 1 >= strlimit - next) {
			int n = len + 4*1024;
			next = allocate(n, PERM);
			strlimit = next + n;
		}
		NEW(p, PERM);
		p->len = len;
		for (p->str = next; str < end; )
			*next++ = *str++;
		*next++ = 0;
		p->link = buckets[h];
		buckets[h] = p;
		return p->str;
	}
}