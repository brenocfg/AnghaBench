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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fread (unsigned char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  xfree (unsigned char*) ; 
 unsigned char* xmalloc (size_t) ; 

__attribute__((used)) static unsigned char *
read_all(FILE *f, size_t *len)
{
	unsigned char *buf;
	size_t ptr, blen;

	blen = 1024;
	buf = xmalloc(blen);
	ptr = 0;
	for (;;) {
		size_t rlen;

		if (ptr == blen) {
			unsigned char *buf2;

			blen <<= 1;
			buf2 = xmalloc(blen);
			memcpy(buf2, buf, ptr);
			xfree(buf);
			buf = buf2;
		}
		rlen = fread(buf + ptr, 1, blen - ptr, f);
		if (rlen == 0) {
			unsigned char *buf3;

			buf3 = xmalloc(ptr);
			memcpy(buf3, buf, ptr);
			xfree(buf);
			*len = ptr;
			return buf3;
		}
		ptr += rlen;
	}
}