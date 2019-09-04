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
typedef  int ssize_t ;
struct TYPE_7__ {unsigned char* rpos; unsigned char* rend; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int EOF ; 
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  F_ERR ; 
 int SIZE_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  feof (TYPE_1__*) ; 
 int getc_unlocked (TYPE_1__*) ; 
 unsigned char* memchr (unsigned char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char*,size_t) ; 
 char* realloc (char*,size_t) ; 

ssize_t getdelim(char **restrict s, size_t *restrict n, int delim, FILE *restrict f)
{
	char *tmp;
	unsigned char *z;
	size_t k;
	size_t i=0;
	int c;

	FLOCK(f);

	if (!n || !s) {
		f->flags |= F_ERR;
		FUNLOCK(f);
		errno = EINVAL;
		return -1;
	}

	if (!*s) *n=0;

	for (;;) {
		z = memchr(f->rpos, delim, f->rend - f->rpos);
		k = z ? z - f->rpos + 1 : f->rend - f->rpos;
		if (i+k+1 >= *n) {
			if (k >= SIZE_MAX/2-i) goto oom;
			size_t m = i+k+2;
			if (!z && m < SIZE_MAX/4) m += m/2;
			tmp = realloc(*s, m);
			if (!tmp) {
				m = i+k+2;
				tmp = realloc(*s, m);
				if (!tmp) goto oom;
			}
			*s = tmp;
			*n = m;
		}
		memcpy(*s+i, f->rpos, k);
		f->rpos += k;
		i += k;
		if (z) break;
		if ((c = getc_unlocked(f)) == EOF) {
			if (!i || !feof(f)) {
				FUNLOCK(f);
				return -1;
			}
			break;
		}
		if (((*s)[i++] = c) == delim) break;
	}
	(*s)[i] = 0;

	FUNLOCK(f);

	return i;
oom:
	f->flags |= F_ERR;
	FUNLOCK(f);
	errno = ENOMEM;
	return -1;
}