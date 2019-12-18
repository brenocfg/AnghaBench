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
typedef  int __uint64_t ;
typedef  scalar_t__ __uint32_t ;

/* Variables and functions */
 int ffs (scalar_t__) ; 

__attribute__((used)) static inline int xfs_lowbit64(__uint64_t v)
{
	__uint32_t	w = (__uint32_t)v;
	int		n = 0;

	if (w) {	/* lower bits */
		n = ffs(w);
	} else {	/* upper bits */
		w = (__uint32_t)(v >> 32);
		if (w && (n = ffs(w)))
		n += 32;
	}
	return n - 1;
}