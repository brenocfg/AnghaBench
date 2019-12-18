#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ulong_t ;
struct TYPE_4__ {size_t str_nbufs; scalar_t__ str_ptr; scalar_t__* str_bufs; scalar_t__ str_bufsz; } ;
typedef  TYPE_1__ strtab_t ;

/* Variables and functions */
 size_t MIN (size_t,size_t) ; 
 int /*<<< orphan*/  bcopy (char const*,size_t,size_t) ; 
 int /*<<< orphan*/  strtab_grow (TYPE_1__*) ; 

__attribute__((used)) static void
strtab_copyin(strtab_t *sp, const char *str, size_t len)
{
	ulong_t b = sp->str_nbufs - 1;
	size_t resid, n;

	while (len != 0) {
		if (sp->str_ptr == sp->str_bufs[b] + sp->str_bufsz) {
			strtab_grow(sp);
			b++;
		}

		resid = sp->str_bufs[b] + sp->str_bufsz - sp->str_ptr;
		n = MIN(resid, len);
		bcopy(str, sp->str_ptr, n);

		sp->str_ptr += n;
		str += n;
		len -= n;
	}
}