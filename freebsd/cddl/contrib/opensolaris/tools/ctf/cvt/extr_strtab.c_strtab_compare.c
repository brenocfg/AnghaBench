#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
struct TYPE_5__ {char const** str_bufs; int str_bufsz; } ;
typedef  TYPE_1__ strtab_t ;
struct TYPE_6__ {size_t str_buf; char* str_data; } ;
typedef  TYPE_2__ strhash_t ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
strtab_compare(strtab_t *sp, strhash_t *hp, const char *str, size_t len)
{
	ulong_t b = hp->str_buf;
	const char *buf = hp->str_data;
	size_t resid, n;
	int rv;

	while (len != 0) {
		if (buf == sp->str_bufs[b] + sp->str_bufsz)
			buf = sp->str_bufs[++b];

		resid = sp->str_bufs[b] + sp->str_bufsz - buf;
		n = MIN(resid, len);

		if ((rv = strncmp(buf, str, n)) != 0)
			return (rv);

		buf += n;
		str += n;
		len -= n;
	}

	return (0);
}