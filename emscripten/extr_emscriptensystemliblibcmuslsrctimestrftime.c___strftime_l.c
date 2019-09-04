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
struct tm {int tm_year; } ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 char* __strftime_fmt_1 (char**,size_t*,char const,struct tm const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 unsigned long strtoul (char const*,char**,int) ; 

size_t __strftime_l(char *restrict s, size_t n, const char *restrict f, const struct tm *restrict tm, locale_t loc)
{
	size_t l, k;
	char buf[100];
	char *p;
	const char *t;
	int plus;
	unsigned long width;
	for (l=0; l<n; f++) {
		if (!*f) {
			s[l] = 0;
			return l;
		}
		if (*f != '%') {
			s[l++] = *f;
			continue;
		}
		f++;
		if ((plus = (*f == '+'))) f++;
		width = strtoul(f, &p, 10);
		if (*p == 'C' || *p == 'F' || *p == 'G' || *p == 'Y') {
			if (!width && p!=f) width = 1;
		} else {
			width = 0;
		}
		f = p;
		if (*f == 'E' || *f == 'O') f++;
		t = __strftime_fmt_1(&buf, &k, *f, tm, loc);
		if (!t) break;
		if (width) {
			for (; *t=='+' || *t=='-' || (*t=='0'&&t[1]); t++, k--);
			width--;
			if (plus && tm->tm_year >= 10000-1900)
				s[l++] = '+';
			else if (tm->tm_year < -1900)
				s[l++] = '-';
			else
				width++;
			for (; width > k && l < n; width--)
				s[l++] = '0';
		}
		if (k > n-l) k = n-l;
		memcpy(s+l, t, k);
		l += k;
	}
	if (n) {
		if (l==n) l=n-1;
		s[l] = 0;
	}
	return 0;
}