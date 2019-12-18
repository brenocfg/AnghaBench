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
 int /*<<< orphan*/  ALIGN_DEST_TO8_DN (unsigned long,unsigned long,long) ; 
 int /*<<< orphan*/  DO_REST_ALIGNED_DN (unsigned long,unsigned long,long) ; 

__attribute__((used)) static inline void __memcpy_aligned_dn (unsigned long d, unsigned long s,
					long n)
{
	s += n;
	d += n;
	ALIGN_DEST_TO8_DN(d,s,n);
	n -= 8;
	while (n >= 0) {
		unsigned long tmp;
		s -= 8;
		__asm__("ldq %0,%1":"=r" (tmp):"m" (*(unsigned long *) s));
		n -= 8;
		d -= 8;
		*(unsigned long *) d = tmp;
	}
	n += 8;
	DO_REST_ALIGNED_DN(d,s,n);
}