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
struct TYPE_7__ {int mode; scalar_t__ rend; scalar_t__ rpos; size_t (* read ) (TYPE_1__*,unsigned char*,size_t) ;} ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  FUNLOCK (TYPE_1__*) ; 
 size_t MIN (scalar_t__,size_t) ; 
 scalar_t__ __toread (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,size_t) ; 
 size_t stub1 (TYPE_1__*,unsigned char*,size_t) ; 

size_t fread(void *restrict destv, size_t size, size_t nmemb, FILE *restrict f)
{
	unsigned char *dest = destv;
	size_t len = size*nmemb, l = len, k;
	if (!size) nmemb = 0;

	FLOCK(f);

	f->mode |= f->mode-1;

	if (f->rend - f->rpos > 0) {
		/* First exhaust the buffer. */
		k = MIN(f->rend - f->rpos, l);
		memcpy(dest, f->rpos, k);
		f->rpos += k;
		dest += k;
		l -= k;
	}
	
	/* Read the remainder directly */
	for (; l; l-=k, dest+=k) {
		k = __toread(f) ? 0 : f->read(f, dest, l);
		if (k+1<=1) {
			FUNLOCK(f);
			return (len-l)/size;
		}
	}

	FUNLOCK(f);
	return nmemb;
}