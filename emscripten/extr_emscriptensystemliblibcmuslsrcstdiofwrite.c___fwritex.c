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
struct TYPE_6__ {size_t wend; size_t wpos; size_t (* write ) (TYPE_1__*,unsigned char const*,size_t) ;scalar_t__ lbf; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 scalar_t__ __towrite (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (size_t,unsigned char const*,size_t) ; 
 size_t stub1 (TYPE_1__*,unsigned char const*,size_t) ; 
 size_t stub2 (TYPE_1__*,unsigned char const*,size_t) ; 

size_t __fwritex(const unsigned char *restrict s, size_t l, FILE *restrict f)
{
	size_t i=0;

	if (!f->wend && __towrite(f)) return 0;

	if (l > f->wend - f->wpos) return f->write(f, s, l);

	if (f->lbf >= 0) {
		/* Match /^(.*\n|)/ */
		for (i=l; i && s[i-1] != '\n'; i--);
		if (i) {
			size_t n = f->write(f, s, i);
			if (n < i) return n;
			s += i;
			l -= i;
		}
	}

	memcpy(f->wpos, s, l);
	f->wpos += l;
	return l+i;
}