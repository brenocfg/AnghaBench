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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  xfree (void*) ; 
 void* xmalloc (size_t) ; 

void *
vector_expand(void *buf,
	size_t esize, size_t *ptr, size_t *len, size_t extra)
{
	size_t nlen;
	void *nbuf;

	if (*len - *ptr >= extra) {
		return buf;
	}
	nlen = (*len << 1);
	if (nlen - *ptr < extra) {
		nlen = extra + *ptr;
		if (nlen < 8) {
			nlen = 8;
		}
	}
	nbuf = xmalloc(nlen * esize);
	if (buf != NULL) {
		memcpy(nbuf, buf, *len * esize);
		xfree(buf);
	}
	*len = nlen;
	return nbuf;
}