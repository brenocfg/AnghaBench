#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mode; unsigned char* rpos; unsigned char* rend; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 size_t MIN (size_t,int) ; 
 int /*<<< orphan*/  feof (TYPE_1__*) ; 
 int getc_unlocked (TYPE_1__*) ; 
 unsigned char* memchr (unsigned char*,char,int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,size_t) ; 

char *fgets(char *restrict s, int n, FILE *restrict f)
{
	char *p = s;
	unsigned char *z;
	size_t k;
	int c;

	FLOCK(f);

	if (n--<=1) {
		f->mode |= f->mode-1;
		FUNLOCK(f);
		if (n) return 0;
		*s = 0;
		return s;
	}

	while (n) {
		z = memchr(f->rpos, '\n', f->rend - f->rpos);
		k = z ? z - f->rpos + 1 : f->rend - f->rpos;
		k = MIN(k, n);
		memcpy(p, f->rpos, k);
		f->rpos += k;
		p += k;
		n -= k;
		if (z || !n) break;
		if ((c = getc_unlocked(f)) < 0) {
			if (p==s || !feof(f)) s = 0;
			break;
		}
		n--;
		if ((*p++ = c) == '\n') break;
	}
	if (s) *p = 0;

	FUNLOCK(f);

	return s;
}